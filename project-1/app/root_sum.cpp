#include <iostream>
#include <ostream>

#include "complex.hpp"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Not enough arguments" << std::endl;
    return 0;
  }

  const std::size_t n{std::stoul(argv[1])};
  const std::size_t k{std::stoul(argv[2])};

  Complex output{Complex::from_cartesian(1, 0)};
  const Complex nth_root{Complex::nth_unity_root(n)};

  Complex accumulator{nth_root};
  for (std::size_t i{1}; i < k; i++) {
    output = output + accumulator;
    accumulator = accumulator * nth_root;
  }

  std::cout << output << std::endl;

  return 0;
}
