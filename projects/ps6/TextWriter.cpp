// Copyright 2024 Wendy Carvalho
#include <iostream>

#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
  const double k = atof(argv[1]);
  const double L = atof(argv[2]);
  std::string text;
  std::string line;
  while (getline(std::cin, line)) {
    text += line;
  }

  RandWriter rw(text, k);
  // std::cout << rw;

  std::string tmp;
  for (int i = 0; i < k; i++) {
    tmp.push_back(text[i]);
  }
  // std::cout << rw.kRand("g") << std::endl;
  std::cout << rw.generate(tmp, L) << std::endl;
  // rw.kRand("gag");
  return 0;
}
