#pragma once

#include <deque>
#include <unordered_map>

#include <SFML/Graphics.hpp>

const unsigned int TILE_SIZE = 40;

enum Direction {
    Up = 0x1, Down = 0x2, Left = 0x4, Right = 0x8,
    Head = 0x10, Tail = 0x20
};

class Snake: public sf::Drawable {
 public:
    Snake(sf::Vector2u pos, int numSeg, Direction dir);

    sf::Vector2u getHead() const { return _positions.front(); }

    void chomp() { _size++; }
    void changeDirection(Direction face) { _facing = face; }
    bool step();
 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
    std::deque<sf::Vector2u> _positions;
    Direction _facing;
    size_t _size;
    std::unordered_map<int, sf::Texture> _textures;
};
