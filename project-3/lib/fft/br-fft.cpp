#include "br-fft.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>

#include "bitrev.hpp"

void BitRevFFT(ComplexVec &vec, const std::size_t n) {
  // NOTE: Step 1, reorganize the array into the bit reversal order

  // TODO: Find a way to not rely in casting here
  const std::size_t log_n{static_cast<std::size_t>(std::log2(n))};

  std::uint64_t rev_counter{0};
  for (std::size_t i{0}; i < n / 2; i++) {
    std::swap(vec[i], vec[rev_counter]);
    std::cout << "Swapping: " << i << ", " << rev_counter << '\n';

    rev_counter = reverse_add(rev_counter, log_n);
  }

  // NOTE: Step 2, ....
}

ComplexVec CopyBitRevFFT(const ComplexVec &vec, const std::size_t n) {
  ComplexVec output{vec};
  BitRevFFT(output, n);

  return output;
}
