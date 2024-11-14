// Copyright 2024 Meriem Elkoudi and Wendy Carvalho
#include <iostream>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EDistanceTest
#include <fstream>
#include "EDistance.hpp"
#include <boost/test/unit_test.hpp>

// wrong cost
BOOST_AUTO_TEST_CASE(testPenalty) {
    std::ifstream file;
    file.open(("startygap.txt"));
    std::string s1, s2;
    file >> s1 >> s2;
    EDistance e(s1, s2);

    BOOST_REQUIRE_EQUAL(1, e.penalty(s1[0], s2[0]));
    // if autograder is upset, check edit distance?????
}

BOOST_AUTO_TEST_CASE(testMin3) {
    std::ifstream file;
    file.open(("example10.txt"));
    std::string s1, s2;
    file >> s1 >> s2;
    EDistance e(s1, s2);
    int a = 1;
    int b = 2;
    int c = 3;
    e.min3(a, b, c);
}

BOOST_AUTO_TEST_CASE(testInvalidArg) {
    EDistance e(" ", " ");
    BOOST_REQUIRE_NO_THROW(e.alignment());
}

BOOST_AUTO_TEST_CASE(testOptDistance) {
    std::ifstream file;
    file.open(("example10.txt"));
    std::string s1, s2;
    file >> s1 >> s2;
    EDistance e(s1, s2);
    BOOST_REQUIRE_EQUAL(e.optDistance(), 7);
}

BOOST_AUTO_TEST_CASE(testAlignment) {
    std::ifstream file;
    file.open(("example10.txt"));
    std::string s1, s2;
    file >> s1 >> s2;
    EDistance e(s1, s2);
    std::string s = "A T 1\nA A 0\nC - 2\nA A 0\nG G 0\nT G 1\nT T 0\nA - 2\nC C 0\nC A 1\n";
    e.optDistance();
    std::string align = e.alignment();
    for (size_t i = 0; i < align.length() - 1; i++) {
        BOOST_REQUIRE_EQUAL(s[i], align[i]);
    }
}

BOOST_AUTO_TEST_CASE(testCutEnds) {
  std::ifstream file;
  file.open(("stx26.txt"));
  std::string s1, s2;
  file >> s1 >> s2;
  EDistance e(s1, s2);
  std::string s =
      "G C 1\nT T 0\nA C 1\nG C 1\nA A 0\nC C 0\nC A 1\nA A 0\n- G 2\nT T 0\nA A 0\n- G 2\nC C 0\nC C 0\nA A 0\n- C 2\n- T 2\nT T 0\nT T 0\nA C 1\nT T 0\nG C 1\nA A 0\n- C 2\nA T 1\nA A 0\n";
  std::string align = e.alignment();
  //std::cout << s << std::endl;
  std::cout << align << std::endl;
  BOOST_REQUIRE_EQUAL(1, 1);
  //BOOST_REQUIRE_EQUAL(align.length(), 155);
  for (size_t i = 0; i < align.length() - 1; i++) {
    BOOST_REQUIRE_EQUAL(s[i], align[i]);
  }
}
