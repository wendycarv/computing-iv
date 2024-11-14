#pragma once

#include <deque>
#include <vector>

#include <SFML/Graphics.hpp>

enum Player { None, Black, Red };

const unsigned int TILE_SIZE = 64;

class Connect4: public sf::Drawable {
 public:
    Connect4(size_t w = 7, size_t h = 6);

    void dropPiece(int col);

    bool isOver() const;
    sf::Vector2u windowSize() { return sf::Vector2u(_width * TILE_SIZE, _height * TILE_SIZE); }
 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
    bool doesWinAtPoint(sf::Vector2i pt, sf::Vector2i qt) const;
    Player _nextPlayer;
    size_t _width, _height;
    sf::Texture _redTexture, _blackTexture;
    std::vector<std::deque<Player> > _grid;
};
