#pragma once

#include <optional>
#include <string_view>
#include <variant>
#include <vector>

#include "complex.hpp"

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

using TokenVariant =
    std::variant<NumberToken, OperatorToken, ImaginaryUnitToken>;

using TokenList = std::vector<TokenVariant>;

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
