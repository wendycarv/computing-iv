// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 1/8/2024
// Copyright 2024 Wendy Carvalho

#include <iostream>
#include <string>
#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>

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

  boost::test_tools::output_test_stream output;
  output << l;
  
  BOOST_TEST(!output.is_empty(false));
  BOOST_TEST(output.check_length(16, true));
  BOOST_TEST(output.is_equal("1011011000110110"));
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


BOOST_AUTO_TEST_CASE(testDifferentSize) {
  FibLFSR l("10110110001101100001");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}
