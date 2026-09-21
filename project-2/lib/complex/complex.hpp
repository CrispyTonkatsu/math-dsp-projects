#pragma once

#include <string>
#include <vector>

class Complex;
std::ostream &operator<<(std::ostream &stream, Complex number);

class ComplexVec;
std::ostream &operator<<(std::ostream &stream, ComplexVec vec);

class Complex {
  double real{0};
  double complex{0};

public:
  Complex() = default;
  ~Complex() = default;

  Complex(const Complex &rhs) = default;
  Complex &operator=(const Complex &rhs) = default;

  Complex(Complex &&rhs) = default;
  Complex &operator=(Complex &&rhs) = default;

  // Custom Constructors
  static Complex from_cartesian(double real, double complex);
  static Complex from_polar(double radius, double angle);

  // Getters
  double get_real() const;
  double get_complex() const;

  double get_radius() const;
  double get_angle() const;

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
  static Complex nth_unity_root(const std::size_t n, const std::size_t k = 1,
                                const double multiplier = 1.0);

  // Unit test functions
  // This will check if they're exactly the same value
  bool operator==(const Complex &other) const;

  friend std::ostream &operator<<(std::ostream &stream, Complex number);
};

inline Complex operator*(double scalar, const Complex &complex) {
  return complex * scalar;
}

inline Complex operator/(double scalar, const Complex &complex) {
  return complex / scalar;
}

class ComplexVec {
  std::vector<Complex> numbers{};

public:
  ComplexVec() = default;
  ComplexVec(std::vector<Complex> &&numbers) : numbers{std::move(numbers)} {}
  ComplexVec(const std::vector<Complex> &numbers) : numbers{numbers} {}

  static ComplexVec from_nth_roots(const std::size_t n,
                                   const double multiplier = 1.0);

  static ComplexVec fourier_basis(const std::size_t n, const std::size_t k,
                                  const double multiplier = 1.0);

  Complex inner_product(const ComplexVec &other) const;
  Complex hadamard_product(const ComplexVec &other) const;

  double length_sq() const;
  double length() const;

  std::string to_string() const;

  Complex &operator[](const std::size_t index);
  const Complex &operator[](const std::size_t index) const;

  const std::vector<Complex> &as_vec() const;

  friend std::ostream &operator<<(std::ostream &stream, ComplexVec vec);
};
