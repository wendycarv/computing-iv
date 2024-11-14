#include "Paddle.hpp"


void Paddle::move(sf::Vector2f vel, float dtsec) {
    _position += vel * dtsec;
}

sf::FloatRect Paddle::bounds() const {
    return sf::FloatRect(
        _position - (_size / 2.f),
        _size
    );
}

void Paddle::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::RectangleShape paddle(_size);
    paddle.setOrigin(_size.x / 2, _size.y / 2);
    paddle.setPosition(_position);
    paddle.setFillColor(sf::Color::White);
    window.draw(paddle, states);
}
