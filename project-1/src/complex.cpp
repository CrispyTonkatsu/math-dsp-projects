#include "complex.hpp"
#include <cmath>
#include <numbers>
#include <string>

Complex Complex::from_cartesian(double real, double complex) {
  Complex output;
  output.real = real;
  output.complex = complex;

  return output;
}

Complex Complex::from_polar(double radius, double angle) {
  Complex output;
  output.real = std::cos(angle) * radius;
  output.complex = std::sin(angle) * radius;

  return output;
}

Complex Complex::conjugate() const { return from_cartesian(real, -complex); }

Complex Complex::operator-() const { return from_cartesian(-real, -complex); }

double Complex::magnitude() const { return std::sqrt(magnitude_squared()); }

double Complex::magnitude_squared() const {
  return real * real + complex * complex;
}

Complex Complex::operator+(const Complex &other) const {
  return from_cartesian(real + other.real, complex + other.complex);
}

Complex Complex::operator-(const Complex &other) const {
  return from_cartesian(real - other.real, complex - other.complex);
}

Complex Complex::operator*(const double scalar) const {
  return from_cartesian(real * scalar, complex * scalar);
}

Complex Complex::operator/(const double scalar) const {
  const double reciprocal{1.0 / scalar};
  return from_cartesian(real * reciprocal, complex * reciprocal);
}

Complex Complex::operator*(const Complex &other) const {
  return from_cartesian(                               //
      (real * other.real) - (complex * other.complex), //
      (real * other.complex) + (complex * other.real));
}

Complex Complex::operator/(const Complex &other) const {
  const Complex numerator{other * this->conjugate()};

  // Taking advantage of z*z_conjugate = a^2 + b^2 for z = a + bi
  const double denominator{1.0 / magnitude_squared()};

  return numerator * denominator;
}

std::string Complex::to_string() const {
  if (complex < 0) {
    return std::to_string(real) + "-" + std::to_string(-complex) + "i";
  }

  return std::to_string(real) + "+" + std::to_string(complex) + "i";
}

Complex Complex::rotate(const double angle) const {
  return *this * from_polar(1, angle);
}

Complex Complex::nth_unity_root(const std::size_t n) {
  return from_polar(1, std::exp((2 * std::numbers::pi_v<double>) / n));
}

bool Complex::operator==(const Complex &other) const {
  return real == other.real && complex == other.complex;
}
