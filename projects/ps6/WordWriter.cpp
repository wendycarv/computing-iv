// Copyright 2024 Wendy Carvalho
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include "WordWriter.hpp"

// Create a Markov model of order k from given text
// Assume that text has length at least k.
WordWriter::WordWriter(const std::string& text, size_t k) {
//   if (text.length() < k) {
//     throw std::invalid_argument("Error: text has to have length at least k words");
//   }
  // read in text word by word
  std::string kgram, word;
  order = k;
  original = text;
  for (size_t i = 0; i < text.length(); i++) {
    if (text[i] != ' ' || text[i] != '\n') {
        word.push_back(text[i]);
    } else {
        dictionary.push_back(word);
        word.clear();
    }
  }
  // sort the alphabet using sort
  std::sort(dictionary.begin(), dictionary.end());
  // traverse thru text in size of k
  // if doesn't already exist in map, add to map
  // increment frequency count
  // kgrams
  char next;
  for (size_t i = 0; i < text.length(); i++) {
    for (size_t j = i; j < i + k; j++) {
      if (kgram.length() < k) {
        if (j >= text.length()) {
          kgram.push_back(text[j - text.length()]);
        } else {
          kgram.push_back(text[j]);
        }
      }
    }
    kGrams[kgram]++;
    if (i + k >= text.length()) {
      next = text[i + k - text.length()];
    } else {
      next = text[i + k];
    }
    k1Grams[kgram][next]++;
    kgram = "";
  }
}

// returns the order k of Markov model
size_t WordWriter::orderK() const { return order; }

// Number of occurences of kgram in text
// Throw an exception if kgram is not length k
// return 0 if not found
int WordWriter::freq(const std::string& kgram) const {
  if (kgram.length() != order) {
    throw std::invalid_argument("Error: kgram is not of length k");
  }
  // if not found return 0
  auto i = kGrams.find(kgram);
  if (i == kGrams.end()) {
    return 0;
  }

  return i->second;
}

// Number of times that character c follows kgram
// if order=0, return num of times that char c appears
// (throw an exception if kgram is not of length k)
// return 0 if not found
int WordWriter::freq(const std::string& kgram, char c) const {
  if (kgram.length() != order) {
    throw std::invalid_argument("Error: kgram is not of length k");
  }

  if (order == 0) {
    int freq = 0;
    for (size_t i = 0; i < original.length(); i++) {
      if (original[i] == c) {
        freq++;
      }
    }
    return freq;
  }

  auto outer = k1Grams.find(kgram);
  if (outer != k1Grams.end()) {
    auto inner = outer->second.find(c);
    if (inner != outer->second.end()) {
      return inner->second;
    }
  }
  return 0;
}

// Random character following given kgram
// (throw an exception if kgram is not of length k)
// (throw an exception if no such kgram)
char WordWriter::kRand(const std::string& kgram) {
  if (kgram.length() != order) {
    throw std::invalid_argument("Error: kgram is not of length k");
  }
  if (kGrams.find(kgram) == kGrams.end()) {
    throw std::invalid_argument("Error: no such kgram");
  }

  auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::minstd_rand0 _gen(seed);
  std::uniform_int_distribution<unsigned int> dist(1, freq(kgram));
  int randK = dist(_gen);

  // std::cout << randK << std::endl;
  // pick a char based on randK
  char randChar;

  int cnt = 0;
  // for (auto& ent1 : k1Grams) {
  //   if (cnt >= randK) {
  //     break;
  //   }
  //   if (ent1.first == kgram) {
  //     for (auto const& ent2 : ent1.second) {
  //       cnt += ent2.second;
  //       if (cnt >= randK) {
  //         randChar = ent2.first;
  //         break;
  //       }
  //     }
  //   }
  // }
  // lambda function to iterate through k1Grams and return randChar
  auto findRandChar =
      [&cnt, &randK, &randChar,
       &kgram](const std::map<std::string, std::map<char, int>>& k1Grams) {
        for (const auto& ent1 : k1Grams) {
          if (cnt >= randK) {
            break;
          }
          if (ent1.first == kgram) {
            for (const auto& ent2 : ent1.second) {
              cnt += ent2.second;
              if (cnt >= randK) {
                randChar = ent2.first;
                break;
              }
            }
          }
        }
      };

  findRandChar(k1Grams);
  return randChar;
}

// Generate a string of length L characters by simulating a trajectory
// through the corresponding Markov chain.  The first k characters of
// the newly generated string should be the argument kgram.
// Throw an exception if kgram is not of length k.
// Assume that L is at least k
std::string WordWriter::generate(const std::string& kgram, size_t L) {
  if (kgram.length() != order) {
    throw std::invalid_argument("Error: kgram is not of length k");
  }
  std::string gen = kgram;
  std::string cpy = kgram;
  char next;
  for (size_t i = 0; i < L - order; i++) {
    next = kRand(cpy);
    gen.push_back(next);
    cpy.erase(cpy.begin());
    cpy.push_back(next);
  }
  // std::cout << gen << std::endl;
  return gen;
}

// Overload the stream insertion operator << and display the internal state
// of the Markov model.  Print out the order, alphabet, and the frequencies
// of the k-grams and k+1-grams
std::ostream& operator<<(std::ostream& os, WordWriter& rw) {
  os << "Order: " << rw.order << std::endl;
  os << "Alphabet: " << rw.alphabet << std::endl;
  os << "Frequencies: " << std::endl;

  // k-grams
  for (auto const& kgram : rw.kGrams) {
    os << kgram.first << ": " << kgram.second << std::endl;
  }
  // k+1-grams
  for (auto const& ent1 : rw.k1Grams) {
    const std::string& kgram = ent1.first;
    for (auto const& ent2 : ent1.second) {
      os << kgram << ", " << ent2.first << ": " << ent2.second << std::endl;
    }
  }
  return os;
}
