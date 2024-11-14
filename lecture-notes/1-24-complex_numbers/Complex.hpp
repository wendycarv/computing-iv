#include <iostream>

class Complex {
  public:
    Complex(double real, double imag): _real(_real), _imag(imag) {}

    static Complex fromPolar(double mag, double angle) {
        return Complex (
            mag * cos(angle)
            mag * sin(angle)
            );
    }

    double real() const { return _real; }
    double imag() const { return _imag; }

    double mag2()const { return (_real * _real + _imag * _imag);}
    double mag() const { return sqr(mag2()); }
    double angle() const { return atan2(_imag, _real); }

    Complex operator+() const { return *this; }
    Complex operator-() const { return Complex(-_real, -_imag); }
    Complex operator~() const { return Complex(_real, -_imag); }
  private:
    const double _real, _imag;
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);


bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

std::ostream& operator<<(std::ostream& os, const Complex& z);