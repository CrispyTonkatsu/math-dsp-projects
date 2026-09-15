#pragma once

#include <cmath>
#include <cstddef>
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
  static Complex from_polar(double radius, double angle);

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
  std::string to_string() const;
  Complex rotate(const double angle) const;
  static Complex nth_unity_root(const std::size_t n);

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

template <std::size_t N> class ComplexVec {
  std::array<Complex, N> numbers{};

public:
  ComplexVec() = default;
  ComplexVec(std::array<Complex, N> numbers) : numbers{numbers} {}

  static ComplexVec from_nth_roots() {
    ComplexVec output{};
    for (std::size_t i{0}; i < N; i++) {
      output.numbers[i] = Complex::nth_unity_root(i);
    }

    return output;
  }

  Complex inner_product(const ComplexVec &other) const {
    Complex total{Complex::from_cartesian(0, 0)};

    for (std::size_t i{0}; i < N; i++) {
      total = numbers[i] * other.numbers[i].conjugate();
    }

    return total;
  }

  double length_sq() const { return inner_product(*this); }
  double length() const { return std::sqrt(length_sq()); }
};
