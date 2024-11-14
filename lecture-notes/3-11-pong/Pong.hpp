#pragma once

#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "Paddle.hpp"

class Pong: public sf::Drawable {
 public:
    Pong(sf::Vector2f windowSize);
    sf::Vector2f windowSize() const { return _windowSize; }

    void step(float dtsec);
 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
 private:
    int _p1Score, _p2Score;
    Paddle _paddle1, _paddle2;
    Ball _ball;
    sf::Vector2f _windowSize;
    sf::Font _font;
};
