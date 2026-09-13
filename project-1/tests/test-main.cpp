#include "parser.hpp"
#include <cassert>

void test(std::string input) { complex_parser::parse_cartesian(input); }

int main() {
  test("22222");
  test("-22222");
  test("-.22222");
  test("2+1i");
  test("2.0+1i");
  test("2+1.0i");
  test("-2+-1i");
  test("-2--1i");
  test("-2.-1ai");

  return 0;
}
