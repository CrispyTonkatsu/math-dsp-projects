#include "bitrev.hpp"

std::uint64_t reverse_add(std::uint64_t bits, std::size_t n) {
  for (std::uint64_t mask{1u << (n - 1)}; mask != 0; mask >>= 1) {
    if ((bits & mask) == 0) {
      bits ^= mask;
      break;
    }

    bits &= ~mask;
  }

  return bits;
}
