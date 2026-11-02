#pragma once

#include "complex.hpp"

namespace filters {
void lowpass(std::vector<Complex> &values, const double a);

void normalize(std::vector<Complex> &values, const double target_db);
}
