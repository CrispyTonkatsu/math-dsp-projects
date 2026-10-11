#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>

#include "br-fft.hpp"
#include "dft.hpp"
#include "fft.hpp"

void check_output(const ComplexVec &data, std::size_t n,
                  std::size_t target_frequency) {
  for (std::size_t i{0}; i < n; i++) {
    const Complex &value{data[i]};
    const double magnitude{value.magnitude()};

    if (i == target_frequency || i == (n - target_frequency)) {
      const double expected_magnitude{static_cast<double>(n) / 2.0};

      assert(std::abs(magnitude - expected_magnitude) < 1e-10 &&
             "Missing peak.");
    } else {
      assert(std::abs(magnitude) < 1e-10 && "Unexpected peak found.");
    }
  }
}

int main() {
  std::cout << "Timing the 3 methods for speed with sin((2\\pi / n) * 4) with "
               "n = 1024\n";

  const std::size_t n{1024};
  const std::size_t target_frequency{4};

  std::vector<Complex> test_data;
  for (std::size_t i{0}; i < n; i++) {
    const double angle{2.0 * std::numbers::pi_v<double> * i * target_frequency /
                       n};
    test_data.push_back(Complex::from_cartesian(std::sin(angle), 0.0));
  }

  const ComplexVec test_wave{test_data};

  std::cout << "Measuring DFT\n";
  const std::chrono::time_point dft_start_time{
      std::chrono::high_resolution_clock::now()};

  const ComplexVec dft_fft_out{DFT(test_wave, n)};

  const std::chrono::time_point dft_end_time{
      std::chrono::high_resolution_clock::now()};

  const auto dft_duration_ns{
      std::chrono::duration_cast<std::chrono::nanoseconds>(dft_end_time -
                                                           dft_start_time)};

  std::cout << "Duration for DFT: " << dft_duration_ns << '\n';
  check_output(dft_fft_out, n, target_frequency);

  std::cout << "Measuring Recursive FFT\n";
  const std::chrono::time_point rec_start_time{
      std::chrono::high_resolution_clock::now()};

  const ComplexVec rec_fft_out{FFT(test_wave, n)};

  const std::chrono::time_point rec_end_time{
      std::chrono::high_resolution_clock::now()};

  const auto rec_duration_ns{
      std::chrono::duration_cast<std::chrono::nanoseconds>(rec_end_time -
                                                           rec_start_time)};

  std::cout << "Duration for Recursive FFT: " << rec_duration_ns << '\n';
  check_output(rec_fft_out, n, target_frequency);

  std::cout << "Measuring Bit Reversal FFT\n";
  const std::chrono::time_point br_start_time{
      std::chrono::high_resolution_clock::now()};

  const ComplexVec br_fft_out{CopyBitRevFFT(test_wave, n)};

  const std::chrono::time_point br_end_time{
      std::chrono::high_resolution_clock::now()};

  const auto br_duration_ns{
      std::chrono::duration_cast<std::chrono::nanoseconds>(br_end_time -
                                                           br_start_time)};

  std::cout << "Duration for Bit Reversal FFT: " << br_duration_ns << '\n';
  check_output(br_fft_out, n, target_frequency);

  // Printing to the output file
  std::ofstream out{"timing.txt"};
  out << std::setw(20) << "DFT" << std::setw(20) << dft_duration_ns << '\n';
  out << std::setw(20) << "Recursive FFT" << std::setw(20) << rec_duration_ns
      << '\n';
  out << std::setw(20) << "Bit Reversal FFT" << std::setw(20)
      << br_duration_ns << '\n';
}
