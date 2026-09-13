class Complex {
  double real{0};
  double complex{0};

  // The rule of 5
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
};

inline Complex operator*(double scalar, const Complex &complex) {
  return complex * scalar;
}

inline Complex operator/(double scalar, const Complex &complex) {
  return complex / scalar;
}
