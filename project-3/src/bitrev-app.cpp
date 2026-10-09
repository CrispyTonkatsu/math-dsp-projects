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
  const std::size_t k{static_cast<std::size_t>(std::sqrt(n))};

  std::uint64_t bits{0};
  for (std::size_t i{0}; i < n; i++) {
    std::cout << std::setw(4) << i << " " << pretty_bitset(i, k) << " "
              << std::setw(4) << bits << " " << pretty_bitset(bits, k) << '\n';

    bits = reverse_add(bits, k);
  }
}
