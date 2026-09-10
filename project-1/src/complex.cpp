#include "complex.hpp"
#include <cmath>

Complex Complex::from_cartesian(double real, double complex) {
  Complex output;
  output.real = real;
  output.complex = complex;

  return output;
}

Complex Complex::from_polar(double angle, double radius) {
  Complex output;
  output.real = std::cos(angle) * radius;
  output.complex = std::sin(angle) * radius;

  return output;
}

Complex Complex::conjugate() const { return from_cartesian(real, -complex); }

Complex Complex::operator-() const { return from_cartesian(-real, -complex); }

Complex Complex::operator+(const Complex &other) const {
  return from_cartesian(real + other.real, complex + other.complex);
}

Complex Complex::operator-(const Complex &other) const {
  return from_cartesian(real - other.real, complex - other.complex);
}

Complex Complex::operator*(const Complex &other) const {
  return from_cartesian(                               //
      (real * other.real) - (complex * other.complex), //
      (real * other.complex) + (complex * other.real));
}

Complex Complex::operator/(const Complex &other) const {
  // TODO: Left off here

  return other;
}
