#pragma once

#include <optional>

#include "tokenizer.hpp"

class TokenCursor {
  std::size_t position{0};
  const TokenList &tokens;

public:
  TokenCursor(const TokenList &tokens);

  std::size_t get_position() const;

  void restore(std::size_t new_position);

  template <typename T> const T *peek() const {
    if (is_end()) {
      return nullptr;
    }

    if (!std::holds_alternative<T>(tokens[position])) {
      return nullptr;
    }

    return &std::get<T>(tokens[position]);
  }

  void consume();

  bool is_end() const;
};

template <typename T, typename F> class Parser {
  F parser_fn;

public:
  using return_type = T;

  explicit Parser(F fn) : parser_fn(std::move(fn)) {}

  std::optional<T> parse(TokenCursor &cursor) const {
    return parser_fn(cursor);
  }
};

template <typename T, typename F> static auto make_parser(F fn) {
  return Parser<T, F>(std::move(fn));
}

template <typename P1, typename P2> auto sequence(const P1 &p1, const P2 &p2) {
  using T1 = typename P1::return_type;
  using T2 = typename P2::return_type;

  return make_parser<std::pair<T1, T2>>(
      [p1, p2](TokenCursor &cursor) -> std::optional<std::pair<T1, T2>> {
        const std::size_t checkpoint{cursor.get_position()};

        auto res1{p1.parse(cursor)};
        if (!res1) {
          cursor.restore(checkpoint);
          return std::nullopt;
        }

        auto res2{p2.parse(cursor)};
        if (!res2) {
          cursor.restore(checkpoint);
          return std::nullopt;
        }

        return std::make_pair(*res1, *res2);
      });
}

template <typename P> auto optional(const P &parser) {
  using T = typename P::return_type;

  return make_parser<std::optional<T>>(
      [parser](TokenCursor &cursor) -> std::optional<std::optional<T>> {
        std::size_t checkpoint{cursor.get_position()};

        auto result{parser.parse(cursor)};
        if (result) {
          return result;
        }

        cursor.restore(checkpoint);

        return std::optional<T>(std::nullopt);
      });
}

template <typename P, typename F> auto map(const P &parser, F mapper) {
  using OldT = typename P::return_type;

  using NewT = std::invoke_result_t<F, OldT>;

  return make_parser<NewT>(
      [parser, mapper](TokenCursor &cursor) -> std::optional<NewT> {
        auto result{parser.parse(cursor)};

        if (!result) {
          return std::nullopt;
        }

        return mapper(*result);
      });
}

template <typename P1, typename P2> auto alt(const P1 &p1, const P2 &p2) {
  using T = typename P1::return_type;
  static_assert(std::is_same_v<T, typename P2::return_type>,
                "alts must both return the same type");

  return make_parser<T>([p1, p2](TokenCursor &cursor) -> std::optional<T> {
    std::size_t checkpoint{cursor.get_position()};

    auto res1{p1.parse(cursor)};
    if (res1) {
      return *res1;
    }

    cursor.restore(checkpoint);

    auto res2{p2.parse(cursor)};
    if (res2) {
      return *res2;
    }

    cursor.restore(checkpoint);

    return std::nullopt;
  });
}

auto match_number();
auto match_op(char character);
auto match_i();

auto match_sign();
auto match_signed_number();
auto match_imaginary_number();

auto match_a();
auto match_bi();
auto match_a_bi();
auto match_bi_a();

auto match_complex();

std::optional<Complex> parse_cartesian(std::string_view string);
