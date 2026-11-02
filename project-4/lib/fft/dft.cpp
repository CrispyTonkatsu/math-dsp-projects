#include "dft.hpp"

ComplexVec DFT(const ComplexVec &input, const std::size_t n) {
  ComplexVec output{std::vector<Complex>{n}};

  for (std::size_t k{0}; k < n; k++) {
    const ComplexVec basis_k{ComplexVec::fourier_basis(n, k)};
    output[k] = input.inner_product(basis_k);
  }

  return output;
}
