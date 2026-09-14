#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

#include "complex.hpp"

namespace complex_parser {
std::optional<Complex> parse_cartesian(std::string_view string);

enum class TokenType {
  Idle,      // Searches for the first valid state to go to
  Number,    // Parses all digits up
  Operator,  // Searches for the operator
  Imaginary, // Appends i token
};

struct NumberToken {
  std::string_view text;

  std::optional<double> to_number() const;
  std::optional<Complex> to_complex(bool is_real) const;
};

struct OperatorToken {
  char character;
};

struct ImaginaryUnitToken {
  char character;
};

template <class... Ts> struct TokenMatcher : Ts... {
  using Ts::operator()...;
};
template <class... Ts> TokenMatcher(Ts...) -> TokenMatcher<Ts...>;

using TokenVariant =
    std::variant<NumberToken, OperatorToken, ImaginaryUnitToken>;

using TokenList = std::vector<TokenVariant>;

template <std::size_t N, typename F, std::size_t... Is>
auto TokenListVisitImpl(F &&visitor, const TokenList &tokens,
                        std::integer_sequence<std::size_t, Is...>) {
  if (tokens.size() != N) {
    throw std::runtime_error("Token count mismatch for pattern match");
  }

  return std::visit(std::forward<F>(visitor), tokens[Is]...);
}

template <std::size_t N, typename F>
auto TokenListVisit(F &&visitor, const TokenList &tokens) {
  return TokenListVisitImpl<N>(std::forward<F>(visitor), tokens,
                               std::make_integer_sequence<std::size_t, N>());
}

bool is_valid_char(char character);
bool is_number_char(char character);
bool is_operator_char(char character);
bool is_imaginary_char(char character);

std::optional<TokenList> tokenize(std::string_view string);

struct TokenResult {
  TokenVariant token;
  std::size_t consumed_count{0};
  bool append_token{true};
};

using TokenizerFunc = std::optional<TokenResult> (*)(std::string_view string,
                                                     std::size_t start_index);

std::optional<TokenResult> try_skip_whitespace(std::string_view string,
                                               std::size_t start_index);

std::optional<TokenResult> try_token_imaginary(std::string_view string,
                                               std::size_t start_index);

std::optional<TokenResult> try_token_number(std::string_view string,
                                            std::size_t start_index);

std::optional<TokenResult> try_token_operator(std::string_view string,
                                              std::size_t start_index);

} // namespace complex_parser
