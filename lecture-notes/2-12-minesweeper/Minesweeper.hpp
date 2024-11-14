#pragma once

#include <SFML/Graphics.hpp>

struct Tile {
   Tile(): isMine(false), isRevealed(false), numMineNeighbors(0) {}
   bool isMine;
   bool isRevealed;
   int numMineNeighbors;
};

class Minesweeper: public sf::Drawable {
 public:
    static const size_t TILE_SIZE = 54;

    Minesweeper(size_t h, size_t w, size_t numMines);

    void click(size_t x, size_t y);
    bool isOver() { return isWon() || isLost(); };
    bool isWon() const;
    bool isLost() const;

    size_t countMines(size_t x, size_t y) const;

    size_t numNeighborMines(size_t x, size_t y) const;
    size_t width() const { return _width; }
    size_t height() const { return _height; }
    size_t size() const { return width() * height(); }

    size_t pixelWidth() const { return _width * TILE_SIZE; }
    size_t pixelHeight() const { return _height * TILE_SIZE; }
 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
    size_t index(size_t x, size_t y) const { return y * _width + x; }; // x + y * width_
    size_t _height;
    size_t _width;
    size_t _numMines;

    std::vector<bool> _minePositions;
    std::vector<size_t> _numMineNeighbors;
    std::vector<Tile> _tiles;

    sf::Texture _unrevealed;
    sf::Texture _mineTexture;
    sf::Texture _flagTexture;
    std::vector<sf::Texture> _emptyTextures;
};
