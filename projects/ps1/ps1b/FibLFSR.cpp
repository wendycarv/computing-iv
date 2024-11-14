// Copyright 2024 Wendy Carvalho
#include "FibLFSR.hpp"
#include <cstring>

namespace PhotoMagic {
FibLFSR::FibLFSR(std::string seed) : initialSeed(seed) {
  // string seed to array?
  int temp = 0;
  int j = 0;
  int i = 0;

  seedSize = seed.length();
  // declare space for bitCharacters using length of given seed + 1 for '\0'
  bitCharacters = new char[seedSize + 1];

  snprintf(bitCharacters, seedSize + 1, "%s", initialSeed.c_str());
  bits = new int[seedSize];
  for (i = 0; i < seedSize; i++) {
    bits[i] = (bitCharacters[i] - '0');
  }

  for (i = 0, j = seedSize - 1; i < j; i++, j--) {
    temp = bits[i];
    bits[i] = bits[j];
    bits[j] = temp;
  }

  for (int i = seedSize - 1; i >= 0; i--) {
    currentState += bits[i] + '0';
  }
  currentState += '\0';
}

// Simulate one step and return the new bit as 0 or 1
int FibLFSR::step() {
  int result;
  // save result of xor with 3 taps: 13, 12, and 10
  result = (((bits[seedSize - 1] ^ bits[13]) ^ bits[12]) ^ bits[10]);

  // shift array bits 1 to left (right in this case)
  for (int i = seedSize - 1; i >= 0; i--) {
    bits[i] = bits[i - 1];
  }

  // add result to end
  bits[0] = result;

  std::ostringstream tmp;
  tmp << *this;

  currentState = tmp.str();
  // return result (0 or 1)
  return result;
}

// Simulate k steps and return a k-bit integer
int FibLFSR::generate(int k) {
  int var = 0;
  // for each bit extracted, double var and add the bit returned by step()
  for (int i = 0; i < k; i++) {
    var *= 2;
    var += step();
  }

  return var;
}

int FibLFSR::getSeedSize() const { return seedSize; }

std::string FibLFSR::getInitialSeed() const { return initialSeed; }

FibLFSR::~FibLFSR() {
  delete[] bitCharacters;
  delete[] bits;
}

std::string FibLFSR::getState() const { return currentState; }

std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr) {
  for (int i = lfsr.seedSize - 1; i >= 0; i--) {
    out << lfsr.bits[i];
  }
  return out;
}
}  // namespace PhotoMagic
