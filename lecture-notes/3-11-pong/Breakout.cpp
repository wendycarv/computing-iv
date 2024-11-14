#include "Breakout.hpp"

#include <algorithm>
#include <functional>

const float BallVel = 150;
const float PaddleVel = 150;
const sf::Vector2f PaddleSize = { 100, 20 };
const sf::Vector2f BrickSize = { 50, 25 };

Breakout::Breakout(sf::Vector2f winSize):
    _paddle1({winSize.x / 2, winSize.y - PaddleSize.y}, PaddleSize),
    _ball({{0, 0}, winSize}, {winSize.x / 2, winSize.y - 2 * PaddleSize.y}, {BallVel, -BallVel}),
    _windowSize(winSize), _isLost(false) {

    for (int x = 0; x < winSize.x / BrickSize.x; x++) {
        for (int y = 0; y < winSize.y / BrickSize.y / 2; y++) {
            _bricks.push_back(Brick({x * BrickSize.x, y * BrickSize.y}, BrickSize));
        }
    }
}


void Breakout::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for (auto& brick : _bricks) {
        window.draw(brick, states);
    }
    // Draw paddles
    window.draw(_paddle1, states);
    // Draw ball
    window.draw(_ball, states);
}

void Breakout::step(float dtsec) {
    float v1 = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        v1 -= PaddleVel;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        v1 += PaddleVel;
    }
    _paddle1.move({v1, 0}, dtsec);
    // Move ball and paddles
    _ball.step(dtsec);
    // check for collisions
    _ball.collide(_paddle1.bounds());
    for (auto& brick : _bricks) {
        if (_ball.collide(brick.bounds())) {
            brick.hit();
        }
    }
    std::remove_if(_bricks.begin(), _bricks.end(), [](auto& b) {
        return !b.isAlive();
    });
    _isLost |= _ball.bottom() >= _windowSize.y;
}