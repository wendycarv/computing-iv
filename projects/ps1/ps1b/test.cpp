// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 1/8/2024
// Copyright 2024 Wendy Carvalho

#include <iostream>
#include <string>

#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;

BOOST_AUTO_TEST_CASE(testStepInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testGenerateInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.generate(9), 51);
}

BOOST_AUTO_TEST_CASE(testGenerate7Steps) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.generate(5), 3);
  BOOST_REQUIRE_EQUAL(l.generate(5), 6);
  BOOST_REQUIRE_EQUAL(l.generate(5), 14);
  BOOST_REQUIRE_EQUAL(l.generate(5), 24);
  BOOST_REQUIRE_EQUAL(l.generate(5), 1);
  BOOST_REQUIRE_EQUAL(l.generate(5), 13);
  BOOST_REQUIRE_EQUAL(l.generate(5), 28);
}

// test operator <<
BOOST_AUTO_TEST_CASE(testOstream) {
  FibLFSR l("1011011000110110");

  std::ostringstream tmp;
  tmp << l;

  std::string strTest = tmp.str();

  BOOST_REQUIRE_EQUAL(strTest, "1011011000110110");
}

// test that the result of # n of step() calls equals generate(n)
BOOST_AUTO_TEST_CASE(testStepEqualsGenerate) {
  FibLFSR l1("1011011000110110");
  FibLFSR l2("1011011000110110");

  for (int i = 0; i < 5; i++) {
    l1.step();
  }

  l2.generate(5);

  std::ostringstream tmp, tmp2;
  tmp << l1;
  tmp2 << l2;

  std::string strStep = tmp.str();
  std::string strGenerate = tmp2.str();

  BOOST_REQUIRE_EQUAL(strStep, strGenerate);
}

BOOST_AUTO_TEST_CASE(testGenerateKBits) {
  FibLFSR l("1011011000110110");
  // array declared w/ max num of bits
  int *binary = new int[16];
  int n = l.generate(10);
  int i;
  for (i = 0; n > 0; i++) {
    binary[0] = n % 2;
    n /= 2;
  }
  delete[] binary;

  BOOST_REQUIRE_LT(i, 10);
}

BOOST_AUTO_TEST_CASE(testDifferentSeed) {
  FibLFSR l2("0011001010000011");
  BOOST_REQUIRE_EQUAL(l2.step(), 0);
  BOOST_REQUIRE_EQUAL(l2.step(), 0);
  BOOST_REQUIRE_EQUAL(l2.step(), 1);
}

BOOST_AUTO_TEST_CASE(testTransform) {
  FibLFSR seed("1011011000110110");

  sf::Image image;
  sf::Color p1, p2;
  // check that images open (later rplc with string)
  if (!image.loadFromFile("cat.jpg")) {
    std::cerr << "failed to open the image" << std::endl;
  }

  p1 = image.getPixel(0, 0);

  transform(image, &seed);
  p2 = image.getPixel(0, 0);

  // check if rgb values before and after are diff
  BOOST_CHECK_NE(p1.r, p2.r);
  BOOST_CHECK_NE(p1.g, p2.g);
  BOOST_CHECK_NE(p1.b, p2.b);
}
