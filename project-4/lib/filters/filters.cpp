#include "filters.hpp"
#include <cmath>

void filters::lowpass(std::vector<Complex> &values, const double a) {
  for (std::size_t i{1}; i < values.size(); i++) {
    values[i] = values[i] + a * values[i - 1];
  }
}

void filters::normalize(std::vector<Complex> &values, const double target_db) {
  double peak{0.0};

  for (const Complex &sample : values) {
    const double abs_sample{std::abs(sample.get_real())};

    if (peak < abs_sample) {
      peak = abs_sample;
    }
  }

  const double target_hz{std::pow(10.0, target_db / 20.0)};
  const double multiplier{target_hz / peak};

  for (Complex &sample : values) {
    sample = sample * multiplier;
  }
}
