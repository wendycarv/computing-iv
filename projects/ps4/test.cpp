// Copyright 2024 Wendy Carvalho

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

#include "CelestialBody.hpp"
#include "Universe.hpp"

BOOST_AUTO_TEST_CASE(testRadius) {
  NB::Universe u("planets.txt");
  BOOST_CHECK_EQUAL(u.radius(), 250000000000);
}

BOOST_AUTO_TEST_CASE(testFlipped) {
  std::ifstream file("massive-squirrel-battle.txt");
  NB::Universe u;
  file >> u;
  BOOST_REQUIRE_CLOSE(u[0].position().y, 3.75e12, 0.1);
}

BOOST_AUTO_TEST_CASE(testFormatted2) {
  std::ifstream file("planets.txt");
  std::ifstream cpy("planets.txt");
  std::stringstream tmp;
  std::string str1, str2;
  double d1, d2;
  NB::Universe u;

  // have universe u read in file
  file >> u;
  // and output contents into tmp
  tmp << u;

  // check numParticles
  // get line from a copy of the file (using orig was not working)
  getline(cpy, str1);
  // get line from output of u
  getline(tmp, str2);
  BOOST_REQUIRE_EQUAL(str1, str2);

  // check radius
  getline(cpy, str1);
  d1 = stod(str1);
  getline(tmp, str2);
  d2 = stod(str2);
  BOOST_REQUIRE_CLOSE(d1, d2, 0.1);

  // check individual celestial bodies in file
  getline(cpy, str1);
  d1 = stod(str1);
  getline(tmp, str2);
  d2 = stod(str2);

  BOOST_REQUIRE_CLOSE(d1, d2, 0.1);
}

BOOST_AUTO_TEST_CASE(testHardcoded) {
  NB::Universe u("planets.txt");
  BOOST_CHECK_EQUAL(u[0].position().y, 0);
}

BOOST_AUTO_TEST_CASE(testStep) {
  NB::Universe u("planets.txt");
  double dt = 25000.0;
  u.step(dt);
  BOOST_REQUIRE_CLOSE(u[0].position().y, 7.4500e+08, 30);
}

BOOST_AUTO_TEST_CASE(testFixedDelta) {
  std::ifstream file("planets.txt");
  std::stringstream tmp;
  std::string str1, str;
  double d1;
  NB::Universe u;

  // have universe u read in file
  file >> u;
  // step
  u.step(5000);
  // and output contents into tmp
  tmp << u;

  // get 2 lines (skip)
  getline(tmp, str1);
  getline(tmp, str1);

  tmp >> str1;
  d1 = stod(str1);
  // std::cout << d1 << std::endl;
  BOOST_REQUIRE_CLOSE(d1, 1.496e+11, 0.01);
  tmp >> str1;
  d1 = stod(str1);
  // std::cout << d1 << std::endl;
  BOOST_REQUIRE_CLOSE(d1, 1.49e+08, 0.01);
}

BOOST_AUTO_TEST_CASE(testAntiGrav) {
  NB::Universe u("planets.txt");
  const double dt = 25000.0;
  u.step(dt);

  BOOST_REQUIRE_CLOSE(u[1].velocity().x, -63.8597221, 0.01);
}

BOOST_AUTO_TEST_CASE(testInverted) {
  NB::Universe u("planets.txt");
  const double dt = 25000.0;
  u.step(dt);
  // std::cout << u;
  BOOST_REQUIRE_LT(u[0].velocity().x, 0);
  BOOST_REQUIRE_CLOSE(u[3].position().x, 3.3087e+01, 0.1);
}

BOOST_AUTO_TEST_CASE(testLeapFrog) {
  NB::Universe u("planets.txt");
  double totalTime = 3.1557600e+7;
  double elapsedTime = 0;
  double dt = 25000.0;
  while (elapsedTime < totalTime) {
    u.step(dt);
    elapsedTime += dt;
  }
  std::cout << u;
  BOOST_REQUIRE_CLOSE(u[0].position().x, 1.4959e+11, 0.1);
  BOOST_REQUIRE_CLOSE(u[0].position().y, -1.6531e+09, 0.1);
  BOOST_REQUIRE_CLOSE(u[1].position().x, -2.2153e+11, 0.1);
  BOOST_REQUIRE_CLOSE(u[1].position().y, -4.9263e+10, 0.1);
  BOOST_REQUIRE_CLOSE(u[2].position().x, 3.4771e+10, 0.1);
  BOOST_REQUIRE_CLOSE(u[2].position().y, 4.5752e+10, 0.1);
  BOOST_REQUIRE_CLOSE(u[3].position().x, 5.9426e+05, 0.1);
  BOOST_REQUIRE_CLOSE(u[3].position().y, 6.2357e+06, 0.1);
  BOOST_REQUIRE_CLOSE(u[4].position().x, -7.3731e+10, 0.1);
  BOOST_REQUIRE_CLOSE(u[4].position().y, -7.9391e+10, 0.1);
}

BOOST_AUTO_TEST_CASE(testExtraCredit) {
  NB::Universe u("planets.txt");
  const double dt = 25000.0;
  u.step(dt);
  // std::cout << u;
  BOOST_REQUIRE_LT(u[0].velocity().x, 0);
  BOOST_REQUIRE_CLOSE(u[3].position().x, 3.3087e+01, 0.1);
}
