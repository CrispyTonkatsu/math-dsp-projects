#include "parser.hpp"
#include <iostream>
#include <ostream>

int main() {
  // Case with 0 tokens (should not work)
  complex_parser::parse_cartesian("");

  // cases with 1 token (That should work)
  std::cout << complex_parser::parse_cartesian("1234")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("-1.0")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("+1.0")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("   i  ")->to_string()
            << std::endl;

  // Cases with 1 token (That should fail)
  complex_parser::parse_cartesian("+1..0");
  complex_parser::parse_cartesian("  + ");
  complex_parser::parse_cartesian("-");

  // cases with 2 tokens (That should work)
  std::cout << complex_parser::parse_cartesian("1.10i")->to_string()
            << std::endl;
  std::cout << complex_parser::parse_cartesian("-i")->to_string() << std::endl;
  std::cout << complex_parser::parse_cartesian("+i")->to_string() << std::endl;

  // cases with 2 tokens (That should fail)
  complex_parser::parse_cartesian("i");

  return 0;
}
