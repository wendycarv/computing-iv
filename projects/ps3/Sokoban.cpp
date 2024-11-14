// Copyright 2024 Wendy Carvalho

#include "Sokoban.hpp"

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace SB {
Sokoban::Sokoban() {
  _wall.loadFromFile("block_06.png");
  _box.loadFromFile("crate_03.png");
  _empty.loadFromFile("ground_01.png");
  _storage.loadFromFile("ground_04.png");
  _player.loadFromFile("player_05.png");
}

Sokoban::Sokoban(std::string filename) {
  std::ifstream file;
  file.open(filename);

  _wall.loadFromFile("block_06.png");
  _box.loadFromFile("crate_03.png");
  _empty.loadFromFile("ground_01.png");
  _storage.loadFromFile("ground_04.png");
  _player.loadFromFile("player_05.png");

  file >> *this;
}

// a >> operator that reads the level from a stream
std::istream& operator>>(std::ifstream& input, Sokoban& game) {
  std::vector<std::vector<char>> staticTiles;
  // first line is 2 ints, h and w
  input >> game._height >> game._width;

  std::string line;
  input.ignore();

  game.origLvl = new char[game._height * game._width];
  // read in the rest of the level content and store inside const * char
  int i;
  for (i = 0; i < game._height; i++) {
    std::getline(input, line);
    for (int j = 0; j < game._width; j++) {
      game.origLvl[i * game._width + j] = line[j];
    }
  }
  // traverse through string, store static tiles in one vector
  // store boxes in sf::Vector2i vector
  // game.boxes.clear();
  char tile;
  for (i = 0; i < game._height; i++) {
    std::vector<char> row;
    for (int j = 0; j < game._width; j++) {
      tile = game.origLvl[i * game._width + j];
      if (tile == '#' || tile == '.' || tile == 'a') {
        row.push_back(tile);
      } else if (tile == '1') {
        row.push_back('a');
        game.boxes.push_back({static_cast<int>(j), static_cast<int>(i)});
      } else if (tile == 'A') {
        row.push_back('.');
        game.boxes.push_back({static_cast<int>(j), static_cast<int>(i)});
      } else if (tile == '@') {
        row.push_back('.');
        game.playerLocation = {static_cast<int>(j), static_cast<int>(i)};
      }
    }
    game.staticTiles.push_back(row);
  }
  delete[] game.origLvl;
  return input;
}
// << operator that writes the level back to a stream
std::ostream& operator<<(std::ostream& output, Sokoban& game) {
  for (int j = 0; j < game._width * game._height; j++) {
    if (j % 10 == 0) {
      std::cout << std::endl;
    }
    std::cout << game.origLvl[j];
  }
  return output;
}

bool Sokoban::isWon() const {
  // // if all boxes are at "a" locations
  // for (int i = 0; i < boxes.size(); i++) {
  //   int x, y;
  //   x = boxes[i].x;
  //   y = boxes[i].y;
  //     if (staticTiles[y][x] != 'a') {
  //       return false;
  //     }
  // }
  auto isBoxAtTarget = [this](const sf::Vector2i& box) {
    int x = box.x;
    int y = box.y;
    return staticTiles[y][x] == 'a';
  };

  auto isStorageFull = [this]() {
    for (size_t yj = 0; yj < staticTiles.size(); yj++) {
      for (size_t xi = 0; xi < staticTiles[yj].size(); xi++) {
        // target
        if (staticTiles[yj][xi] == 'a') {
          bool foundBox = false;
          for (const auto& box : boxes) {
            size_t x = box.x;
            size_t y = box.y;
            if (x == xi && y == yj) {
              foundBox = true;
              break;
            }
          }
          if (!foundBox) {
            return false;  // at least one storage is not filled
          }
        }
      }
    }
    return true;  // all storage is filled
  };
  // check if all boxes are at "a" locations
  return std::all_of(boxes.begin(), boxes.end(), isBoxAtTarget) ||
         isStorageFull();
  // return true;
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // draw walls for every tile location
  // need to update later to make grid properly
  for (int y = 0; y < _height; y++) {
    for (int x = 0; x < _width; x++) {
      sf::Sprite tile;
      sf::Sprite box;
      sf::Vector2f tmp;
      sf::Sprite player;
      // check game grid
      if (staticTiles[y][x] == '#') {
        tile.setTexture(_wall);
      } else if (staticTiles[y][x] == '.') {
        tile.setTexture(_empty);
      } else if (staticTiles[y][x] == 'a') {
        tile.setTexture(_storage);
      }
      // while boxes vector is not empty
      for (auto& b : boxes) {
        box.setTexture(_box);
        tmp = sf::Vector2f(b);
        tmp.x *= TILE_SIZE;
        tmp.y *= TILE_SIZE;
        box.setPosition(tmp);
        target.draw(box, states);
      }

      player.setTexture(_player);
      tmp = sf::Vector2f(playerLocation);
      tmp.x *= TILE_SIZE;
      tmp.y *= TILE_SIZE;

      // if position is equal to a wall, don't move
      player.setPosition(tmp);
      target.draw(player, states);

      tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
      target.draw(tile, states);
    }
  }
}

// implement playerLoc()
sf::Vector2i Sokoban::playerLoc() const { return playerLocation; }

void Sokoban::movePlayer(Direction dir) {
  // up
  if (dir == Up) {
    _player.loadFromFile("player_08.png");
    sf::Vector2i currPos = {playerLocation.x, playerLocation.y};
    sf::Vector2i newPos = {playerLocation.x, playerLocation.y - 1};
    sf::Vector2i nextTo = {playerLocation.x, playerLocation.y - 2};
    if (playerLocation.y != 0) {
      if (staticTiles[playerLocation.y - 1][playerLocation.x] != '#') {
        previousPLoc.push_back(std::make_pair(false, playerLocation));
        playerLocation.y = playerLocation.y - 1;
      }
    }
    for (size_t i = 0; i < boxes.size(); i++) {
      if (boxes[i] == newPos) {
        if ((staticTiles[newPos.y - 1][newPos.x] != '#' && newPos.y != 0) &&
            (std::find(boxes.begin(), boxes.end(), nextTo) == boxes.end())) {
          // previousPLoc.push_back(playerLocation);
          previousBLoc.push_back(std::make_pair(i, boxes[i]));
          boxes[i] = {newPos.x, newPos.y - 1};
          previousPLoc.push_back(std::make_pair(true, currPos));

          playerLocation = newPos;
        } else {
          playerLocation = currPos;
          previousPLoc.pop_back();
        }
      }
    }
  }
  // down
  if (dir == Down) {
    _player.loadFromFile("player_05.png");
    sf::Vector2i currPos = {playerLocation.x, playerLocation.y};
    sf::Vector2i newPos = {playerLocation.x, playerLocation.y + 1};
    sf::Vector2i nextTo = {playerLocation.x, playerLocation.y + 2};
    if (playerLocation.y != _height - 1) {
      if (staticTiles[playerLocation.y + 1][playerLocation.x] != '#') {
        previousPLoc.push_back(std::make_pair(false, playerLocation));
        playerLocation.y = playerLocation.y + 1;
      }
    }

    for (size_t i = 0; i < boxes.size(); i++) {
      if (boxes[i] == newPos) {
        if ((staticTiles[newPos.y + 1][newPos.x] != '#' &&
             newPos.y + 1 < _height) &&
            (std::find(boxes.begin(), boxes.end(), nextTo) == boxes.end())) {
          previousBLoc.push_back(std::make_pair(i, boxes[i]));
          boxes[i] = {newPos.x, newPos.y + 1};
          previousPLoc.push_back(std::make_pair(true, currPos));

          playerLocation = newPos;
        } else {
          playerLocation = currPos;
        }
      }
    }
  }

  // left
  if (dir == Left) {
    _player.loadFromFile("player_20.png");
    sf::Vector2i currPos = {playerLocation.x, playerLocation.y};
    sf::Vector2i newPos = {playerLocation.x - 1, playerLocation.y};
    sf::Vector2i nextTo = {playerLocation.x - 2, playerLocation.y};
    if (staticTiles[newPos.y][newPos.x] != '#' && playerLocation.x - 1 >= 0) {
      previousPLoc.push_back(std::make_pair(false, playerLocation));
      playerLocation = newPos;
    }

    for (size_t i = 0; i < boxes.size(); i++) {
      if (boxes[i] == newPos) {
        if ((staticTiles[newPos.y][newPos.x - 1] != '#' && newPos.x != 0) &&
            (std::find(boxes.begin(), boxes.end(), nextTo) == boxes.end())) {
          previousBLoc.push_back(std::make_pair(i, boxes[i]));
          boxes[i] = {newPos.x - 1, newPos.y};
          previousPLoc.push_back(std::make_pair(true, currPos));

          playerLocation = newPos;

        } else {
          playerLocation = currPos;
        }
      }
    }
  }
  // right
  if (dir == Right) {
    _player.loadFromFile("player_17.png");
    sf::Vector2i currPos = {playerLocation.x, playerLocation.y};
    sf::Vector2i newPos = {playerLocation.x + 1, playerLocation.y};
    sf::Vector2i nextTo = {playerLocation.x + 2, playerLocation.y};
    if (staticTiles[newPos.y][newPos.x] != '#' &&
        playerLocation.x + 1 != _width) {
      previousPLoc.push_back(std::make_pair(false, playerLocation));
      playerLocation = newPos;
    }

    for (size_t i = 0; i < boxes.size(); i++) {
      if (boxes[i] == newPos) {
        if ((staticTiles[newPos.y][newPos.x + 1] != '#' &&
             newPos.x + 1 != _width) &&
            (std::find(boxes.begin(), boxes.end(), nextTo) == boxes.end())) {
          previousBLoc.push_back(std::make_pair(i, boxes[i]));
          boxes[i] = {newPos.x + 1, newPos.y};
          previousPLoc.push_back(std::make_pair(true, currPos));

          playerLocation = newPos;
        } else {
          playerLocation = currPos;
        }
      }
    }
  }
}

void Sokoban::undo() {
  if (!previousPLoc.empty()) {
    auto lastElement = previousPLoc.back();
    if (lastElement.first == true) {
      playerLocation = lastElement.second;
      previousPLoc.pop_back();
      auto lastElement = previousBLoc.back();
      boxes[lastElement.first] = lastElement.second;
      previousBLoc.pop_back();
    } else {
      playerLocation = lastElement.second;
      previousPLoc.pop_back();
    }
  }
}
};  // namespace SB
