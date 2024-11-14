#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Ball.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"

class Breakout: public sf::Drawable {
 public:
    Breakout(sf::Vector2f windowSize);
    sf::Vector2f windowSize() const { return _windowSize; }

    void step(float dtsec);

    bool isGameOver() const { return _isLost || _bricks.empty(); }
 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
 private:
    Paddle _paddle1;
    Ball _ball;
    sf::Vector2f _windowSize;
    std::vector<Brick> _bricks;
    bool _isLost;
};
