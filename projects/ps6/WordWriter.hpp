// Copyright 2024 Wendy Carvalho
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>

class WordWriter {
 public:
  // Create a Markov model of order k from given text
  // Assume that text has length at least k.
  WordWriter(const std::string& text, size_t k);

  // returns the order k of Markov model
  size_t orderK() const;

  // Number of occurences of kgram in text
  // Throw an exception if kgram is not length k
  // return 0 if not found
  int freq(const std::string& kgram) const;

  // Number of times that character c follows kgram
  // if order=0, return num of times that char c appears
  // (throw an exception if kgram is not of length k)
  // return 0 if not found
  int freq(const std::string& kgram, char c) const;

  // Random character following given kgram
  // (throw an exception if kgram is not of length k)
  // (throw an exception if no such kgram)
  char kRand(const std::string& kgram);

  // Generate a string of length L characters by simulating a trajectory
  // through the corresponding Markov chain.  The first k characters of
  // the newly generated string should be the argument kgram.
  // Throw an exception if kgram is not of length k.
  // Assume that L is at least k
  std::string generate(const std::string& kgram, size_t L);

  friend std::ostream& operator<<(std::ostream& os, WordWriter& rw);

 private:
  std::map<std::string, std::map<char, int>> k1Grams;
  std::map<std::string, int> kGrams;
  std::vector<std::string> dictionary;
  std::string original;
  size_t order;
};
// Overload the stream insertion operator << and display the internal state
// of the Markov model.  Print out the order, alphabet, and the frequencies
// of the k-grams and k+1-grams
