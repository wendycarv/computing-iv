#pragma once

#include <SFML/Graphics.hpp>

class Ball: public sf::Drawable {
 public:
    Ball(sf::FloatRect bounds, sf::Vector2f pos, sf::Vector2f vel, float rad = 10):
        _position(pos), _velocity(vel), _radius(rad), _boundary(bounds) {}
    void step(float dtsec);

    bool collide(sf::FloatRect box);

    float left() const { return _position.x - _radius; }
    float right() const { return _position.x + _radius; }
    float bottom() const { return _position.y + _radius; }
 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
 private:
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    const float _radius;
    sf::FloatRect _boundary;
};