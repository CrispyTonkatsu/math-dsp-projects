#include "parser.hpp"

#include <cctype>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <optional>
#include <ostream>
#include <variant>

std::optional<Complex>
complex_parser::parse_cartesian(std::string_view string) {
  std::optional<TokenList> tokens_opt{complex_parser::tokenize(string)};

  if (!tokens_opt.has_value()) {
    return std::nullopt;
  }

  TokenList tokens{tokens_opt.value()};

  const std::size_t token_count{tokens.size()};

  std::cout << "Token Count: " << token_count << std::endl;

  std::optional<Complex> output{Complex::from_cartesian(0, 0)};

  switch (token_count) {
  case 1: {
    output = std::visit(
        TokenMatcher{
            [](NumberToken &num) -> std::optional<Complex> {
              std::optional<double> real{num.to_number()};

              return std::make_optional(
                  Complex::from_cartesian(real.value(), 0));
            },
            [](auto &) -> std::optional<Complex> { return std::nullopt; },
        },
        tokens[0]);
  }
  default:
    break;
  }

  return output;
}

std::optional<double> complex_parser::NumberToken::to_number() const {
  double real{};
  std::from_chars_result result{
      std::from_chars(text.begin(), text.end(), real)};

  if (result.ptr != text.end()) {
    std::cout << "Invalid number " << text << std::endl;
    return std::nullopt;
  }

  return real;
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
  TokenType state{TokenType::Idle};
  TokenType previous_state{TokenType::Idle};

  std::size_t index{0};
  std::size_t state_start_index{0};

  const auto change_state = [&](TokenType next_state) {
    previous_state = state;
    state = next_state;
    state_start_index = index;
  };

  const std::size_t length{string.length()};

  while (index < length) {
    const char &current_character{string[index]};

    switch (state) {
    case TokenType::Idle: {
      if (is_number_char(current_character)) {
        change_state(TokenType::Number);
        output.emplace_back(NumberToken());

      } else if (is_operator_char(current_character)) {
        if (previous_state == TokenType::Number) {
          change_state(TokenType::Operator);
          output.emplace_back(OperatorToken());

        } else {
          change_state(TokenType::Number);
          output.emplace_back(NumberToken());
          index++;
        }

      } else if (is_imaginary_char(current_character)) {
        change_state(TokenType::Imaginary);
        output.emplace_back(ImaginaryUnitToken());

      } else if (std::isspace(current_character)) {
        index++;

      } else {
        std::cerr << "[Tokenizer:Idle] Invalid character found: \""
                  << current_character << "\" at index: " << index << " in "
                  << string << "\n";
        return std::nullopt;
      }
    } break;

    case TokenType::Number: {
      NumberToken &token{std::get<NumberToken>(output.back())};

      char digit{current_character};
      while (is_number_char(digit) && index < string.length()) {
        digit = string[index];

        if (!is_valid_char(digit)) {
          std::cerr << "[Tokenizer:Number] Invalid character found: \"" << digit
                    << "\" at index: " << index << " in " << string << "\n";
          return std::nullopt;
        }

        index++;
      }

      token.text = string.substr(state_start_index, index - state_start_index);

      change_state(TokenType::Idle);
    } break;

    case TokenType::Operator: {
      OperatorToken &token{std::get<OperatorToken>(output.back())};

      index++;
      token.character = current_character;

      change_state(TokenType::Idle);
    } break;

    case TokenType::Imaginary: {
      ImaginaryUnitToken &token{std::get<ImaginaryUnitToken>(output.back())};

      index++;
      token.character = current_character;

      change_state(TokenType::Idle);
    } break;
    }
  }

  return output;
}
