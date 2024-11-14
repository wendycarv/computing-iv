#pragma once
#include <random>

#include <SFML/Graphics.hpp>

#include "Snake.hpp"

class Game: public sf::Drawable {
 public:
    Game(unsigned int width = 20, unsigned int height = 20);

    bool isGameover() const { return _gameover; }

    void step();
    void changeDirection(Direction face) { _snake.changeDirection(face); }
    sf::Vector2u windowSize() const { return sf::Vector2u(_size.x * TILE_SIZE, _size.y * TILE_SIZE); }
 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
 private:
    sf::Vector2u randPos();

    bool _gameover;
    Snake _snake;
    sf::Vector2u _size;
    sf::Vector2u _applePos;
    sf::Texture _appleTexture;
    std::minstd_rand0 _gen;
};
