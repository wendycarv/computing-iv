// Copyright 2024 Wendy Carvalho

#include <fstream>
#include <iostream>
#include <string>

#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

using SB::Sokoban;

// check <<
BOOST_AUTO_TEST_CASE(testInsertion) {
  std::ifstream lvlFile;
  SB::Sokoban s;
  lvlFile.open("level1.lvl");
  lvlFile >> s;
  BOOST_CHECK_EQUAL(s.height(), 10);
}

BOOST_AUTO_TEST_CASE(testBoxWall) {
  std::ifstream lvlFile;
  SB::Sokoban s;
  lvlFile.open("level1.lvl");
  lvlFile >> s;

  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Left);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);

  sf::Vector2u currLoc = static_cast<sf::Vector2u>(s.playerLoc());
  sf::Vector2u tmp = {5, 2};

  BOOST_CHECK_EQUAL(currLoc.x, tmp.x);
  BOOST_CHECK_EQUAL(currLoc.y, tmp.y);
}


BOOST_AUTO_TEST_CASE(testBoxBox) {
  std::ifstream lvlFile;
  SB::Sokoban s;
  lvlFile.open("level2.lvl");
  lvlFile >> s;

  s.movePlayer(SB::Direction::Up);

  sf::Vector2u currLoc = static_cast<sf::Vector2u>(s.playerLoc());
  sf::Vector2u tmp = {8, 5};

  BOOST_CHECK_EQUAL(currLoc.x, tmp.x);
  BOOST_CHECK_EQUAL(currLoc.y, tmp.y);
}

BOOST_AUTO_TEST_CASE(testLotsOfBoxes) {
  std::ifstream lvlFile;
  SB::Sokoban s;
  lvlFile.open("level5.lvl");
  lvlFile >> s;

  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Up);

  BOOST_CHECK_EQUAL(s.isWon(), true);
}

BOOST_AUTO_TEST_CASE(testLotsOfTargets) {
  std::ifstream lvlFile;
  SB::Sokoban s;
  lvlFile.open("level6.lvl");
  lvlFile >> s;
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Left);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Up);
  s.movePlayer(SB::Direction::Right);
  s.movePlayer(SB::Direction::Down);

  BOOST_CHECK_EQUAL(s.isWon(), true);
}

BOOST_AUTO_TEST_CASE(testSymbol) {
  std::ifstream lvlFile;
  SB::Sokoban s;
  lvlFile.open("check1.lvl");

  lvlFile >> s;
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Left);
  s.movePlayer(SB::Direction::Left);
  // BOOST_CHECK_EQUAL(s.isWon(), true);

  sf::Vector2u currLoc = static_cast<sf::Vector2u>(s.playerLoc());
  sf::Vector2u tmp = {1, 3};

  BOOST_CHECK_EQUAL(currLoc.x, tmp.x);
  BOOST_CHECK_EQUAL(currLoc.y, tmp.y);
}

BOOST_AUTO_TEST_CASE(testMoveOffScreen) {
  SB::Sokoban s("level4.lvl");
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Left);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);
  s.movePlayer(SB::Direction::Down);

  sf::Vector2u currLoc = static_cast<sf::Vector2u>(s.playerLoc());
  sf::Vector2u tmp = {5, 7};

  BOOST_CHECK_EQUAL(currLoc.x, tmp.x);
  BOOST_CHECK_EQUAL(currLoc.y, tmp.y);
}
