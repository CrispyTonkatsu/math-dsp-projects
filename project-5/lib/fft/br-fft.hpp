#pragma once

#include "complex.hpp"

void BitRevFFT(ComplexVec &vec, const std::size_t n);

ComplexVec CopyBitRevFFT(const ComplexVec &vec, const std::size_t n);
