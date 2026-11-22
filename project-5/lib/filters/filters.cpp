#include "filters.hpp"
#include <cmath>

void filters::normalize(std::vector<Complex>& values, const double target_db) {
  if (values.empty()) {
    return;
  }

  double peak{0.0};

  for (const Complex& sample: values) {
    const double abs_sample{std::abs(sample.get_real())};

    if (peak < abs_sample) {
      peak = abs_sample;
    }
  }

  const double target_hz{std::pow(10.0, target_db / 20.0)};
  const double multiplier{target_hz / peak};

  for (Complex& sample: values) {
    sample = sample * multiplier;
  }
}
