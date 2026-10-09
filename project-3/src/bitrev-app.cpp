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

  // TODO: Prettify the printing here
  std::uint64_t bits{0};
  for (std::size_t i{0}; i < n; i++) {
    std::cout << "Output " << i << " " << bits << '\n';
    bits = reverse_add(bits, k);
  }
}
