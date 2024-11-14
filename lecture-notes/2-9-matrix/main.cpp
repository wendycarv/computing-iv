#include "matrix.hpp"

#include <iostream>

int main() {
    const Matrix<int> m(3,4);
    // m(2, 1) = 1;
    std::cout << m(2, 1) << std::endl;
    return 0;
}