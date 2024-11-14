// Copyright 2024 Dr. Daly
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Bracket Tests

#include <fstream>
#include <string>
#include <sstream>

#include <boost/test/included/unit_test.hpp>

#include "bracket.hpp"

void runTrial(const std::string& infile, const std::string& expfile) {
    std::ifstream fin(infile);
    std::ifstream expin(expfile);
    int numLines;
    fin >> numLines;
    fin.get();  // Burn extra newline
    for (int i = 0; i < numLines; i++) {
        std::string line;
        std::getline(fin, line);
        std::string resultStr;
        expin >> resultStr;
        bool result = resultStr == "Yes";
        BOOST_REQUIRE_EQUAL(isMatched(line), result);
    }
}

BOOST_AUTO_TEST_CASE(TestBlank) {
    BOOST_REQUIRE(isMatched(""));
}

BOOST_AUTO_TEST_CASE(TestChevrons) {
    BOOST_REQUIRE(isMatched("<>"));
}

BOOST_AUTO_TEST_CASE(TestLBrace) {
    BOOST_REQUIRE(!isMatched("{"));
}

BOOST_AUTO_TEST_CASE(TestRBrace) {
    BOOST_REQUIRE(!isMatched("}"));
}

BOOST_AUTO_TEST_CASE(TestReverse) {
    BOOST_REQUIRE_EQUAL(isMatched("><"), false);
}

BOOST_AUTO_TEST_CASE(TestSequential) {
    BOOST_REQUIRE_EQUAL(isMatched("()[]{}<>"), true);
}

BOOST_AUTO_TEST_CASE(TestNasher) {
    runTrial("nasher.txt", "nasherExp.txt");
}

BOOST_AUTO_TEST_CASE(TestTazib) {
    runTrial("tazib.txt", "tazibExp.txt");
}

BOOST_AUTO_TEST_CASE(TestMorass) {
    runTrial("morass.txt", "morassExp.txt");
}
