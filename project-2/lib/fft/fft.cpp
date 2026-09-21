#include "fft.hpp"

ComplexVec FFT(const ComplexVec &input, const std::size_t n) {
  if (n == 1) {
    return input;
  }

  std::vector<Complex> even_vec;
  std::vector<Complex> odd_vec;

  for (std::size_t i{0}; i < n; i++) {
    if (i % 2 == 0) {
      even_vec.push_back(input[i]);
    } else {
      odd_vec.push_back(input[i]);
    }
  }

  const ComplexVec even_terms{FFT(even_vec, n / 2)};
  const ComplexVec odd_terms{FFT(odd_vec, n / 2)};

  ComplexVec output{std::vector<Complex>{n}};
  for (std::size_t k{0}; k < n / 2; k++) {
    const Complex omega{Complex::nth_unity_root(n, k, -1.0)};

    output[k] = even_terms[k] + omega * odd_terms[k];
    output[k + n / 2] = even_terms[k] - omega * odd_terms[k];
  }

  return output;
}
