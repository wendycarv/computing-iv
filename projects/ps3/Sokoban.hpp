// Copyright 2024 Wendy Carvalho
#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SB {
enum Direction {
  Up = sf::Keyboard::Up,
  Down = sf::Keyboard::Down,
  Left = sf::Keyboard::Left,
  Right = sf::Keyboard::Right,
};

class Sokoban : public sf::Drawable {
 public:
  static const size_t TILE_SIZE = 64;
  Sokoban();
  explicit Sokoban(std::string filename);
  size_t width() const { return _width; }
  size_t height() const { return _height; }

  sf::Vector2i playerLoc() const;  // returns player's current position

  void movePlayer(Direction dir);
  void resetBoxes() { boxes.clear(); }
  void undo();

  bool isWon() const;

  bool soundIsPlaying() { return victoryMusic; }

  void setPlayingTrue() { victoryMusic = true; }

  // a >> operator that reads the level from a stream
  friend std::istream& operator>>(std::ifstream& input, Sokoban& game);
  // << operator that writes the level back to a stream
  friend std::ostream& operator<<(std::ostream& output, Sokoban& game);

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  int _height;
  int _width;

  bool victoryMusic;

  sf::Texture _wall;
  sf::Texture _box;
  sf::Texture _empty;
  sf::Texture _storage;
  sf::Texture _player;

  char* origLvl;

  std::vector<std::vector<char>> staticTiles;
  std::vector<sf::Vector2i> boxes;
  sf::Vector2i playerLocation;
  std::vector<std::pair<bool, sf::Vector2i>> previousPLoc;
  std::vector<std::pair<int, sf::Vector2i>> previousBLoc;
};

};  // namespace SB
