// Copyright 2024 Wendy Carvalho

#include <iostream>

#include "FibLFSR.hpp"

int main() {
  PhotoMagic::FibLFSR flfsr("1011011000110110");
  int result = 0;

  // calling step() 10 times:
  for (int i = 0; i < 10; i++) {
    result = flfsr.step();
    std::cout << flfsr << " " << result << std::endl;
  }

  std::cout << std::endl;

  // calling generate() 7 times:
  for (int i = 0; i < 7; i++) {
    result = flfsr.generate(5);
    std::cout << flfsr << " " << result << std::endl;
  }

  return 0;
}
