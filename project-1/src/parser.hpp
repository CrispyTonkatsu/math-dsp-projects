#pragma once

#include <optional>
#include <string_view>
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

bool is_valid_char(char character);
bool is_number_char(char character);
bool is_operator_char(char character);
bool is_imaginary_char(char character);

std::optional<TokenList> tokenize(std::string_view string);
} // namespace complex_parser
