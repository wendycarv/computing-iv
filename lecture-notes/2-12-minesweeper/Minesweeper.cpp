#include "Minesweeper.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
 
Minesweeper::Minesweeper(size_t h, size_t w, size_t numMines)
    : _height(h), _width(w), _numMines(numMines), _tiles(h*w) { //_minePositions(h * w, false), _numMineNeighbors(h*w, 0)
  for (size_t i = 0; i < _numMines; i++) {
    _tiles[i].isMine = true;
  }

  std::minstd_rand0 gen(std::chrono::system_clock::now().time_since_epoch().count());
  //std::shuffle(_minePositions.begin(), _minePositions.end(), gen);
  std::shuffle(_tiles.begin(), _tiles.end(), gen);

  for(size_t x=0; x<_width;x++) {
    for(size_t y=0; y<_height;y++) {
      //_numMineNeighbors[index(x,y)] = countMines(x, y);
      _tiles[index(x,y)].numMineNeighbors = countMines(x, y);
    }
  }

  _unrevealed.loadFromFile("images/MINESWEEPER_X.png");
  _mineTexture.loadFromFile("images/MINESWEEPER_M.png");
  _flagTexture.loadFromFile("images/MINESWEEPER_F.png");

  _emptyTextures.resize(9);
  for (size_t i = 0; i <= 8; i++) {
    std::string filename = "images/MINESWEEPER_0.png";
    filename.replace(19, 1, 1, ('0' + i));
    _emptyTextures[i].loadFromFile(filename);
  }
}

void Minesweeper::click(size_t x, size_t y) {
  if(_tiles[index(x,y)].isRevealed) return;
  
  _tiles[index(x,y)].isRevealed = true;
 
  if (_tiles[index(x,y)].numMineNeighbors == 0) {
    size_t xmin = std::clamp(x - 1, 0ul, x);
    size_t xmax = std::clamp(x + 1, 0ul, _width-1);
    size_t ymin = std::clamp(y - 1, 0ul, y);
    size_t ymax = std::clamp(y + 1, 0ul, _height-1);

    for (size_t xi = xmin; xi <= xmax; xi++) {
      for (size_t yj = ymin; yj <= ymax; yj++) {
          click(xi,yj);

      }
    }
  }
}


bool Minesweeper::isWon()const {
  return std::all_of(_tiles.begin(), _tiles.end(), [](const Tile& t) {
    return t.isMine || t.isRevealed;
  });
}
bool Minesweeper::isLost()const {
  return std::all_of(_tiles.begin(), _tiles.end(), [](const Tile& t) {
    return t.isMine && t.isRevealed;
  });
}

size_t Minesweeper::countMines(size_t x, size_t y) const {
  size_t xmin = std::clamp(x - 1, 0ul, x);
  size_t xmax = std::clamp(x + 1, 0ul, _width-1);
  size_t ymin = std::clamp(y - 1, 0ul, y);
  size_t ymax = std::clamp(y + 1, 0ul, _height-1);

  size_t result = 0;
  for (size_t xi = xmin; xi <= xmax; xi++) {
    for (size_t yj = ymin; yj <= ymax; yj++) {
       if (_tiles[index(xi, yj)].isMine) result++;
    }
  }
  return result;
}

size_t Minesweeper::numNeighborMines(size_t x, size_t y) const {
  size_t result = 0;
  for (size_t xi = x-1; xi <= x + 1; xi++) {
    for(size_t yj = x - 1; yj <= y + 1; yj++) {
      result += _minePositions[index(xi, yj)];
    }
  }
  return result;
}

void Minesweeper::draw(sf::RenderTarget& target,
                       sf::RenderStates states) const {
  for (size_t y = 0; y < height(); y++) {
    for (size_t x = 0; x < width(); x++) {
      sf::Sprite tile;
      if (!_tiles[index(x,y)].isRevealed) {
        tile.setTexture(_unrevealed);
      } else if (_tiles[index(x, y)].isMine) {
        tile.setTexture(_mineTexture);
      } else {
        tile.setTexture(_emptyTextures[_tiles[index(x,y)].numMineNeighbors]);  // TODO: number
      }
      //tile.setTexture(_unrevealed);  // TODO: pick the right one
      tile.scale({0.25, 0.25});
      tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
      target.draw(tile, states);
    }
  }
}