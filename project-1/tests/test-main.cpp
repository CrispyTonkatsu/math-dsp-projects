#include "parser.hpp"
#include <iostream>
#include <ostream>

int main() {
  // case with 0 tokens (should not work)
  complex_parser::parse_cartesian("");

  // cases with 1 token (that should work)
  std::cout << complex_parser::parse_cartesian("1234")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian(".1234")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("i")->to_string() << std::endl;

  // cases with 2 tokens
  std::cout << complex_parser::parse_cartesian("-1234")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("+.1234")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("-i")->to_string() << std::endl;
  std::cout << complex_parser::parse_cartesian("1i")->to_string() << std::endl;

  // cases with 3 tokens
  std::cout << complex_parser::parse_cartesian("-1i")->to_string() << std::endl;

  // cases with 4 tokens
  std::cout << complex_parser::parse_cartesian("1+1i")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("1-1i")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("1i-1")->to_string()
            << std::endl;

  // cases with 5 tokens
  std::cout << complex_parser::parse_cartesian("-1-1i")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("-1i-1")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("1i--1")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("1--1i")->to_string()
            << std::endl;

  // cases with 6 tokens
  std::cout << complex_parser::parse_cartesian("+1--1i")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("+1i--1")->to_string()
            << std::endl;

  return 0;
}
