// Copyright 2024 Wendy Carvalho
#include <fstream>
#include <iostream>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RandWriter
#include <boost/test/unit_test.hpp>

#include "RandWriter.hpp"

BOOST_AUTO_TEST_CASE(testOrderK) {
  int order = 3;
  RandWriter rw("gagggagaggcgagaaa", order);
  BOOST_REQUIRE_EQUAL(rw.orderK(), order);
}
BOOST_AUTO_TEST_CASE(testKRand) {
  RandWriter rw("gagggagaggcgagaaa", 1);
  char c = rw.kRand("g");
  std::cout << c << std::endl;
  BOOST_REQUIRE(c == 'g' || c == 'a' || c == 'c');
  // BOOST_REQUIRE(c != 'W');
}
BOOST_AUTO_TEST_CASE(testKRandNoThrow) {
  RandWriter rw("gagggagaggcgagaaa", 1);
  BOOST_REQUIRE_NO_THROW(rw.kRand("g"));
}
BOOST_AUTO_TEST_CASE(testKRandThrow) {
  RandWriter rw("gagggagaggcgagaaa", 1);
  BOOST_REQUIRE_THROW(rw.kRand("test"), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(testFreq) {
  RandWriter rw("gagggagaggcgagaaa", 1);
  BOOST_REQUIRE_EQUAL(rw.freq("a"), 7);
  BOOST_REQUIRE_EQUAL(rw.freq("g"), 9);
  BOOST_REQUIRE_EQUAL(rw.freq("c"), 1);
}
BOOST_AUTO_TEST_CASE(testFreqWChar) {
  RandWriter rw("gagggagaggcgagaaa", 1);
  BOOST_REQUIRE_EQUAL(rw.freq("a", 'a'), 2);
  BOOST_REQUIRE_EQUAL(rw.freq("a", 'g'), 5);
  BOOST_REQUIRE_EQUAL(rw.freq("c", 'g'), 1);
  BOOST_REQUIRE_EQUAL(rw.freq("g", 'a'), 5);
  BOOST_REQUIRE_EQUAL(rw.freq("g", 'c'), 1);
  BOOST_REQUIRE_EQUAL(rw.freq("g", 'g'), 3);
}
BOOST_AUTO_TEST_CASE(testGenerateLength) {
  size_t length = 10;
  RandWriter rw("gagggagaggcgagaaa", 2);
  std::string str = rw.generate("ga", length);
  BOOST_REQUIRE_EQUAL(str.length(), length);
}
BOOST_AUTO_TEST_CASE(testGenerateStart) {
  size_t length = 10;
  std::string kgram = "gag";
  RandWriter rw("gagggagaggcgagaaa", 3);
  std::string str = rw.generate(kgram, length);
  BOOST_REQUIRE_EQUAL(kgram, str.substr(0, 3));
}
BOOST_AUTO_TEST_CASE(testFreq2) {
  RandWriter rw("gagggagaggcgagaaa", 3);
  BOOST_REQUIRE_EQUAL(rw.freq("aaa"), 1);
  BOOST_REQUIRE_EQUAL(rw.freq("aga"), 3);
  BOOST_REQUIRE_EQUAL(rw.freq("agg"), 2);
  BOOST_REQUIRE_EQUAL(rw.freq("cga"), 1);
  BOOST_REQUIRE_EQUAL(rw.freq("cgc"), 0);
  BOOST_REQUIRE_EQUAL(rw.freq("gag"), 4);
  BOOST_REQUIRE_EQUAL(rw.freq("ggg"), 1);
  BOOST_REQUIRE_EQUAL(rw.freq("gga"), 1);
  BOOST_REQUIRE_EQUAL(rw.freq("ggc"), 1);
  BOOST_REQUIRE_EQUAL(rw.freq("gcg"), 1);
}
