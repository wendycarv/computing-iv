// Copyright 2024 Wendy Carvalho

#pragma once

#ifndef FIBLFSR_HPP
#define FIBLSFR_HPP

#include <array>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

namespace PhotoMagic {
class FibLFSR {
  public:
    // Constructor to create LFSR with the given initial seed
    explicit FibLFSR(std::string seed);
    // Simulate one step and return the new bit as 0 or 1
    int step();
    // Simulate k steps and return a k-bit integer
    int generate(int k);

    int getSeedSize() const;

    std::string getInitialSeed() const;

    std::string getState() const;

    friend std::ostream& operator<<(std::ostream&, const FibLFSR& lfsr);
    ~FibLFSR();

  private:
    // Any fields that you need
    const std::string initialSeed;
    std::string currentState;
    char* bitCharacters;
    int* bits;
    int seedSize;
};

}  // namespace PhotoMagic

int numOfBits(int num);

#endif
