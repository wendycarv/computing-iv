#include "Pong.hpp"

const float BallVel = 150;
const float PaddleVel = 150;
const sf::Vector2f PaddleSize = { 20, 100 };

Pong::Pong(sf::Vector2f winSize):
    _p1Score(0), _p2Score(0),
    _paddle1({PaddleSize.x, winSize.y / 2}, PaddleSize),
    _paddle2({winSize.x - PaddleSize.x, winSize.y / 2}, PaddleSize),
    _ball({{0, 0}, winSize}, {winSize.x / 2, winSize.y / 2}, {BallVel, BallVel}),
    _windowSize(winSize) {
    _font.loadFromFile("Roboto-Regular.ttf");
}


void Pong::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    // Draw scores
    sf::Text scoreLabel1(std::to_string(_p1Score), _font);
    scoreLabel1.setFillColor(sf::Color::White);
    scoreLabel1.setPosition(_windowSize.x / 4, 0);
    scoreLabel1.setOrigin(scoreLabel1.getLocalBounds().width / 2, 0);
    window.draw(scoreLabel1, states);
    sf::Text scoreLabel2(std::to_string(_p2Score), _font);
    scoreLabel2.setFillColor(sf::Color::White);
    scoreLabel2.setPosition(_windowSize.x * 3 / 4, 0);
    scoreLabel2.setOrigin(scoreLabel2.getLocalBounds().width / 2, 0);
    window.draw(scoreLabel2, states);
    // Draw paddles
    window.draw(_paddle1, states);
    window.draw(_paddle2, states);
    // Draw ball
    window.draw(_ball, states);
}

void Pong::step(float dtsec) {
    float v1 = 0;
    float v2 = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        v1 -= PaddleVel;
        v2 -= PaddleVel;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        v1 += PaddleVel;
        v2 += PaddleVel;
    }
    _paddle1.move({0, v1}, dtsec);
    _paddle2.move({0, v2}, dtsec);
    // Move ball and paddles
    _ball.step(dtsec);
    // check for collisions
    _ball.collide(_paddle1.bounds());
    _ball.collide(_paddle2.bounds());

    if (_ball.left() <= 0) {
        _p2Score++;
    } else if (_ball.right() >= _windowSize.x) {
        _p1Score++;
    }
}