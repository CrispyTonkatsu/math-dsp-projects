#include "filters.hpp"

void filters::lowpass(std::vector<Complex> &values, const float a) {
  for (std::size_t i{1}; i < values.size(); i++) {
    values[i] = values[i] + a * values[i - 1];
  }
}
