#include "parser.hpp"
#include "tokenizer.hpp"

#include <optional>
#include <string_view>

TokenCursor::TokenCursor(const TokenList &tokens) : tokens(tokens) {};

std::size_t TokenCursor::get_position() const { return position; }

void TokenCursor::restore(std::size_t new_position) { position = new_position; }

void TokenCursor::consume() { position++; }

bool TokenCursor::is_end() const { return position >= tokens.size(); }

auto match_number() {
  return make_parser<double>([](TokenCursor &cursor) -> std::optional<double> {
    const NumberToken *token{cursor.peek<NumberToken>()};
    if (!token) {
      return std::nullopt;
    }

    const std::optional<double> double_opt{token->to_number()};
    if (!double_opt.has_value()) {
      return std::nullopt;
    }

    cursor.consume();
    return double_opt.value();
  });
}

auto match_op(char character) {
  return make_parser<char>(
      [character](TokenCursor &cursor) -> std::optional<char> {
        const OperatorToken *token{cursor.peek<OperatorToken>()};
        if (!token) {
          return std::nullopt;
        }

        if (token->character != character) {
          return std::nullopt;
        }

        cursor.consume();
        return token->character;
      });
}

auto match_i() {
  return make_parser<char>([](TokenCursor &cursor) -> std::optional<char> {
    const ImaginaryUnitToken *token{cursor.peek<ImaginaryUnitToken>()};
    if (!token) {
      return std::nullopt;
    }

    cursor.consume();
    return token->character;
  });
}

auto match_sign() {
  return alt(map(match_op('+'), [](auto) { return 1.0; }),
             map(match_op('-'), [](auto) { return -1.0; }));
}

auto match_signed_number() {
  return map(sequence(optional(match_sign()), match_number()),
             [](const std::pair<std::optional<double>, double> &pair) {
               return pair.first.value_or(1.0) * pair.second;
             });
}

auto match_imaginary_number() {
  return map(sequence(match_signed_number(), match_i()),
             [](const std::pair<double, char> &pair) {
               return Complex::from_cartesian(0, pair.first);
             });
}

auto match_a() {
  return map(match_signed_number(), [](const double &value) {
    return Complex::from_cartesian(value, 0);
  });
}

auto match_bi() { return match_imaginary_number(); }

auto match_a_bi() {
  return map(             //
      sequence(match_a(), //
               map(sequence(match_sign(), match_bi()),
                   [](const std::pair<double, Complex> &value) {
                     return value.first * value.second;
                   })),
      [](const std::pair<Complex, Complex> &value) {
        return value.first + value.second;
      });
}

auto match_bi_a() {
  return map(              //
      sequence(match_bi(), //
               map(sequence(match_sign(), match_a()),
                   [](const std::pair<double, Complex> &value) {
                     return value.first * value.second;
                   })),
      [](const std::pair<Complex, Complex> &value) {
        return value.first + value.second;
      });
}

auto match_complex() {
  return alt(alt(match_a_bi(), match_bi_a()), alt(match_bi(), match_a()));
}

std::optional<Complex> parse_cartesian(std::string_view string) {
  std::optional<TokenList> tokens_opt{tokenize(string)};

  if (!tokens_opt.has_value()) {
    return std::nullopt;
  }

  TokenCursor cursor{tokens_opt.value()};
  return match_complex().parse(cursor);
}
