#include <cmath>
#include <complex>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// format operator for output of complex type:

ostream &operator<<(ostream &out, complex<double> c) {
  if (c.imag() < 0) {
    out << c.real() << c.imag() << "i";
  } else {
    out << c.real() << "+" << c.imag() << "i";
  }
  return out;
}

int main(int, char *argv[]) {

  int N;
  sscanf(argv[1], "%d", &N);

  const double PI = 4.0 * atan(1.0), TWOPI = 2.0 * PI;

  complex<double> *inputs;
  inputs = new complex<double>[N];

  ifstream f1(argv[2]);

  for (int i = 0; i < N; i++) {

    if (f1) {
      char buf[50];
      f1.getline(buf, 50);
      double d1 = 0, d2 = 0;
      sscanf(buf, "%lf %lf", &d1, &d2);
      complex<double> c1(d1, d2);
      inputs[i] = c1;
    }
  }

  cout << setprecision(6);

  for (int j = 0; j < N; j++) {
    double abs1 = abs(inputs[j]);
    double arg1 = arg(inputs[j]);
    double arg2 = arg1 / TWOPI;
    cout << inputs[j] << endl;
    cout << "polar form:  " << abs1 << "*e^i" << arg2 << "*2PI" << endl;
  }

  delete[] inputs;

  return 0;
}
