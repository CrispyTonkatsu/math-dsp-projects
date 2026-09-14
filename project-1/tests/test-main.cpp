#include "parser.hpp"

int main() {
  parse_cartesian("1");
  parse_cartesian("+1");
  parse_cartesian("-100");
  parse_cartesian("-100i");

  parse_cartesian("-100i+1234");
  parse_cartesian("100i-1234");

  parse_cartesian("100-1234i");
  parse_cartesian("-100-1234i");

  parse_cartesian("-100+-1234i");
  parse_cartesian("-100-+1234i");

  return 0;
}
