#include <fstream>
#include <iostream>
#include <string>
#include "brainfuck.hpp"

int main(int argc, const char* argv[]) {
  // get program
  std::ifstream fin(argv[1]);
  // set up interpreter
  Brainfuck bf(fin);
  // run
  bf.run(std::cin, std::cout);
}