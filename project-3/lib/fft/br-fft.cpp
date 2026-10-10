#include "br-fft.hpp"

void BitRevFFT(ComplexVec &vec, const std::size_t n) { 
}

ComplexVec CopyBitRevFFT(const ComplexVec &vec, const std::size_t n) {
  ComplexVec output{vec};
  BitRevFFT(output, n);

  return output;
}
