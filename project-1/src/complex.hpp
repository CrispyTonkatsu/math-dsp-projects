#pragma once

#include <string>

class Complex {
  double real{0};
  double complex{0};

  // The rule of 5 (Being explicit because I find it helpful)
  Complex() = default;

public:
  ~Complex() = default;

  Complex(const Complex &rhs) = default;
  Complex &operator=(const Complex &rhs) = default;

  Complex(Complex &&rhs) = default;
  Complex &operator=(Complex &&rhs) = default;

  // Custom Constructors
  static Complex from_cartesian(double real, double complex);
  static Complex from_polar(double angle, double radius);

  // Common operations
  Complex conjugate() const;
  Complex operator-() const;

  double magnitude() const;
  double magnitude_squared() const;

  Complex operator+(const Complex &other) const;
  Complex operator-(const Complex &other) const;

  Complex operator*(const double scalar) const;
  Complex operator/(const double scalar) const;

  Complex operator*(const Complex &other) const;
  Complex operator/(const Complex &other) const;

  // Utilities

  // TODO: Add a precision argument
  std::string to_string() const;

  // Unit test functions
  // This will check if they're exactly the same value
  bool operator==(const Complex &other) const;
};

inline Complex operator*(double scalar, const Complex &complex) {
  return complex * scalar;
}

inline Complex operator/(double scalar, const Complex &complex) {
  return complex / scalar;
}

inline std::ostream &operator<<(std::ostream &stream, Complex number) {
  stream << number.to_string();
  return stream;
}
