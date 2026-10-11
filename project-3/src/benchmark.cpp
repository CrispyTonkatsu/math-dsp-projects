#include <cassert>
#include <cmath>
#include <iostream>

#include "br-fft.hpp"
#include "dft.hpp"
#include "fft.hpp"
#include "utils.hpp"

void check_output(const ComplexVec &data, std::size_t n,
                  std::size_t target_frequency) {
  for (std::size_t i{0}; i < n; i++) {
    const Complex &value{data[i]};
    const double magnitude{value.magnitude()};

    if (i == target_frequency || i == (n - target_frequency)) {
      const double expected_magnitude{static_cast<double>(n) / 2.0};

      assert(std::abs(magnitude - expected_magnitude) < 1e-2 &&
             "Missing peak.");
    } else {
      assert(std::abs(magnitude) < 1e-2 && "Unexpected peak found.");
    }
  }
}

int main() {
  std::cout << "Benchmarking the 3 methods for speed with an impulse\n";

  const std::size_t n{1024};
  const std::size_t target_frequency{4};

  std::vector<Complex> test_data;
  for (std::size_t i{0}; i < n; i++) {
    const double angle{2.0 * std::numbers::pi_v<double> * i * target_frequency /
                       n};
    test_data.push_back(Complex::from_cartesian(std::sin(angle), 0.0));
  }

  const ComplexVec test_wave{test_data};
  const auto br_fft_out{CopyBitRevFFT(test_wave, n)};
  check_output(br_fft_out, n, target_frequency);
}
