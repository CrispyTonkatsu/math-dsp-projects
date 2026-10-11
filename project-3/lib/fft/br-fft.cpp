#include "br-fft.hpp"
#include <cmath>

#include "bitrev.hpp"

void BitRevFFT(ComplexVec &vec, const std::size_t n) {
  const std::size_t log_n{log2(n)};

  std::uint64_t rev_counter{0};
  for (std::size_t i{0}; i < n / 2; i++) {
    std::swap(vec[i], vec[rev_counter]);
    rev_counter = reverse_add(rev_counter, log_n);
  }

  for (std::size_t stage{0}; stage < log_n; stage++) {
    const std::size_t half_size{1u << stage};
    const std::size_t block_size{2u * half_size};

    for (std::size_t block{0}; block < n; block += block_size) {
      for (std::size_t pair{0}; pair < half_size; pair++) {
        const std::size_t a{block + pair};
        const std::size_t b{block + pair + half_size};

        const Complex w{Complex::nth_unity_root(block_size, pair, -1.0)};
        const Complex new_a{vec[a] + w * vec[b]};
        const Complex new_b{vec[a] - w * vec[b]};

        vec[a] = new_a;
        vec[b] = new_b;
      }
    }
  }
}

ComplexVec CopyBitRevFFT(const ComplexVec &vec, const std::size_t n) {
  ComplexVec output{vec};
  BitRevFFT(output, n);

  return output;
}
