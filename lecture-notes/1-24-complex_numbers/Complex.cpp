#include "Complex.hpp"

Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(
        lhs.real() + rhs.real(), 
        lhs.imag() + rhs.imag());
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(
        lhs.real() - rhs.real(), 
        lhs.imag() - rhs.imag());
}

bool operator==(const Complex& lhs, const Complex& rhs) {
    return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Complex& z) {
    if (z.imag() == 0) {
        os << z.real();
    } else if (z.real() == 0) {
        os << z.imag() << "i";
    } else if (z.imag() > 0 ) {
        os << z.real() << " + " << z.imag() << "i";
    } else {
        os << z.real() << " - " << -z.imag() << "i";
    }
}