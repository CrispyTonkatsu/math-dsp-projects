#include <cmath>
#include <iomanip>
#include <iostream>

#include "bitrev.hpp"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Missing bit count parameter.\n";
    return 0;
  }

  const std::size_t n{std::stoul(argv[1])};

  // TODO: Find a way to not rely on casting here
  const std::size_t log_n{static_cast<std::size_t>(std::log2(n))};

  std::uint64_t bits{0};
  for (std::size_t i{0}; i < n; i++) {
    std::cout << std::setw(4) << i << " " << pretty_bitset(i, log_n) << " "
              << std::setw(4) << bits << " " << pretty_bitset(bits, log_n)
              << '\n';

    bits = reverse_add(bits, log_n);
  }
}
