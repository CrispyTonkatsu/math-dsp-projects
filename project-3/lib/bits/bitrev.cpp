#include "bitrev.hpp"
#include <bit>

std::size_t log2(std::uint64_t bits) { return std::countr_zero(bits); }

std::uint64_t reverse_add(std::uint64_t bits, std::size_t bit_count) {
  for (std::uint64_t mask{1u << (bit_count - 1)}; mask != 0; mask >>= 1) {
    if ((bits & mask) == 0) {
      bits ^= mask;
      break;
    }

    bits &= ~mask;
  }

  return bits;
}

std::string pretty_bitset(std::uint64_t bits, std::size_t bit_count) {
  std::string output;

  for (std::uint64_t mask{1u << (bit_count - 1)}; mask != 0; mask >>= 1) {
    if ((bits & mask) == 0) {
      output.append("0");

    } else {
      output.append("1");
    }
  }

  return output;
}
