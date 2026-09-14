#include "parser.hpp"

#include <array>
#include <cctype>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <optional>
#include <ostream>
#include <string_view>

inline std::nullopt_t print_error(const char *message,
                                  const complex_parser::TokenList &tokens) {
  using namespace complex_parser;
  std::cerr << "[Parser] " << message << " : (";

  for (const TokenVariant &token : tokens) {
    std::visit(
        TokenMatcher{
            [](const NumberToken &num) { std::cout << num.text << "/"; },
            [](const ImaginaryUnitToken &img) {
              std::cout << img.character << "/";
            },
            [](const OperatorToken &op) { std::cout << op.character << "/"; },
        },
        token);
  }

  std::cout << ")" << std::endl;

  return std::nullopt;
}

std::optional<Complex>
complex_parser::parse_cartesian(std::string_view string) {
  std::optional<TokenList> tokens_opt{complex_parser::tokenize(string)};

  if (!tokens_opt.has_value()) {
    return std::nullopt;
  }

  const TokenList &tokens{tokens_opt.value()};

  const std::size_t token_count{tokens.size()};

  if (token_count == 0) {
    print_error("There are no tokens", tokens);
    return std::nullopt;
  }

  switch (token_count) {
  case 1:
    return TokenListVisit<1>( //
        TokenMatcher{
            [](const NumberToken &num) -> std::optional<Complex> {
              return num.to_complex(true);
            },
            [](const ImaginaryUnitToken &) -> std::optional<Complex> {
              return Complex::from_cartesian(0, 1);
            },
            [tokens](const auto &) -> std::optional<Complex> {
              return print_error("Invalid Number", tokens);
            },
        },
        tokens);

  case 2:
    return TokenListVisit<2>( //
        TokenMatcher{
            [](const NumberToken &num,
               const ImaginaryUnitToken &) -> std::optional<Complex> { //
              return num.to_complex(false);
            },
            [](const OperatorToken &op,
               const ImaginaryUnitToken &) -> std::optional<Complex> {
              int sign{1};
              if (op.character == '-') {
                sign = -1;
              }
              return Complex::from_cartesian(0, sign);
            },
            [tokens](const auto &, const auto &) -> std::optional<Complex> {
              return print_error("Invalid Number", tokens);
            },
        },
        tokens);
  }

  return std::nullopt;
}

std::optional<double> complex_parser::NumberToken::to_number() const {
  if (text.size() == 0) {
    std::cout << "[Parser:Number] Corrupt number, it should never be of size 0"
              << std::endl;
    return std::nullopt;
  }

  if (text.size() == 1 && is_operator_char(text[0])) {
    std::cout << "[Parser:Number] Invalid number: " << text << std::endl;
    return std::nullopt;
  }

  const std::size_t offset{text[0] == '+' ? 1u : 0u};

  double number{};
  std::from_chars_result result{
      std::from_chars(text.begin() + offset, text.end(), number)};

  if (result.ptr != text.end()) {
    std::cout << "[Parser:Number] Invalid number " << text << std::endl;
    return std::nullopt;
  }

  return number;
}

std::optional<Complex>
complex_parser::NumberToken::to_complex(bool is_real) const {
  const std::optional<double> number_opt{to_number()};

  if (!number_opt.has_value()) {
    return std::nullopt;
  }

  return is_real ? Complex::from_cartesian(number_opt.value(), 0)
                 : Complex::from_cartesian(0, number_opt.value());
}

bool complex_parser::is_valid_char(char character) {
  return is_number_char(character) || is_operator_char(character) ||
         is_imaginary_char(character) || character == ' ';
}

bool complex_parser::is_number_char(char character) {
  return std::isdigit(character) || character == '.';
}

bool complex_parser::is_operator_char(char character) {
  return character == '+' || character == '-';
}

bool complex_parser::is_imaginary_char(char character) {
  return character == 'i';
}

std::optional<complex_parser::TokenList>
complex_parser::tokenize(std::string_view string) {
  TokenList output{};

  std::size_t index{0};
  const std::size_t length{string.length()};

  const std::array<TokenizerFunc, 4> tokenizers{
      try_skip_whitespace, try_token_imaginary, try_token_number,
      try_token_operator};

  while (index < length) {

    bool failed{true};
    for (TokenizerFunc tokenizer : tokenizers) {
      std::optional<TokenResult> result{tokenizer(string, index)};

      if (!result.has_value()) {
        continue;
      }

      if (result.value().append_token) {
        output.push_back(result.value().token);
      }

      index += result.value().consumed_count;

      failed = false;
      break;
    }

    if (failed) {
      std::cerr << "[Tokenizer] Invalid string: " << string.substr(0, index - 1)
                << " -> " << string[index] << " <- "
                << string.substr(index, string.length() - index) << std::endl;
      return std::nullopt;
    }
  }

  return output;
}

std::optional<complex_parser::TokenResult>
complex_parser::try_skip_whitespace(std::string_view string,
                                    std::size_t start_index) {
  if (string[start_index] != ' ') {
    return std::nullopt;
  }

  std::size_t index{start_index};
  while (index < string.length()) {
    if (string[index] != ' ') {
      break;
    }

    index++;
  }

  return TokenResult{
      .token{ImaginaryUnitToken{}},
      .consumed_count = index - start_index,
      .append_token = false,
  };
}

std::optional<complex_parser::TokenResult>
complex_parser::try_token_imaginary(std::string_view string,
                                    std::size_t start_index) {
  if (!is_imaginary_char(string[start_index])) {
    return std::nullopt;
  }

  return TokenResult{
      .token{ImaginaryUnitToken{
          .character = string[start_index],
      }},
      .consumed_count = 1,
  };
}

std::optional<complex_parser::TokenResult>
complex_parser::try_token_number(std::string_view string,
                                 std::size_t start_index) {
  std::size_t index{start_index};
  if (is_operator_char(string[start_index])) {
    index++;
  }

  for (; index < string.length(); index++) {
    const char digit{string[index]};

    if (!is_valid_char(digit)) {
      return std::nullopt;
    }

    if (!is_number_char(digit)) {
      break;
    }
  }

  const size_t number_length{index - start_index};

  if (number_length == 0) {
    return std::nullopt;
  }

  if (number_length == 1 && is_operator_char(string[start_index])) {
    return std::nullopt;
  }

  return TokenResult{
      .token{NumberToken{
          .text{string.substr(start_index, number_length)},
      }},
      .consumed_count = number_length,
  };
}

std::optional<complex_parser::TokenResult>
complex_parser::try_token_operator(std::string_view string,
                                   std::size_t start_index) {
  if (!is_operator_char(string[start_index])) {
    return std::nullopt;
  }

  return TokenResult{
      .token{OperatorToken{
          .character = string[start_index],
      }},
      .consumed_count = 1,
  };
}
