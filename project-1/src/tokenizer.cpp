#include "tokenizer.hpp"

#include <array>
#include <charconv>
#include <iostream>

std::optional<double> NumberToken::to_number() const {
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

std::optional<Complex> NumberToken::to_complex(bool is_real) const {
  const std::optional<double> number_opt{to_number()};

  if (!number_opt.has_value()) {
    return std::nullopt;
  }

  return is_real ? Complex::from_cartesian(number_opt.value(), 0)
                 : Complex::from_cartesian(0, number_opt.value());
}

bool is_valid_char(char character) {
  return is_number_char(character) || is_operator_char(character) ||
         is_imaginary_char(character) || character == ' ';
}

bool is_number_char(char character) {
  return std::isdigit(character) || character == '.';
}

bool is_operator_char(char character) {
  return character == '+' || character == '-';
}

bool is_imaginary_char(char character) { return character == 'i'; }

std::optional<TokenList> tokenize(std::string_view string) {
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
      std::cerr << "[Tokenizer] Invalid string: " << string << std::endl;
      return std::nullopt;
    }
  }

  return output;
}

std::optional<TokenResult> try_skip_whitespace(std::string_view string,
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

std::optional<TokenResult> try_token_imaginary(std::string_view string,
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

std::optional<TokenResult> try_token_number(std::string_view string,
                                            std::size_t start_index) {
  std::size_t index{start_index};
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

std::optional<TokenResult> try_token_operator(std::string_view string,
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
