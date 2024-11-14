#include "Ball.hpp"


void Ball::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    sf::CircleShape ball(_radius);
    ball.setOrigin(_radius, _radius);
    ball.setPosition(_position);
    ball.setFillColor(sf::Color(0xFFAAAAFF));
    window.draw(ball, states);
}

void Ball::step(float dtsec) {
    _position += _velocity * dtsec;
    // Collide with window boundary
    if (_position.x - _radius <= _boundary.left) {
        _velocity.x *= -1;
        _position.x = _boundary.left + _radius;
    }
    if (_position.x + _radius >= _boundary.left + _boundary.width) {
        _velocity.x *= -1;
        _position.x = _boundary.left + _boundary.width - _radius;
    }
    if (_position.y - _radius <= _boundary.top) {
        _velocity.y *= -1;
        _position.y = _boundary.top + _radius;
    }
    if (_position.y + _radius >= _boundary.top + _boundary.height) {
        _velocity.y *= -1;
        _position.y = _boundary.top + _boundary.height - _radius;
    }
}


bool Ball::collide(sf::FloatRect box) {
    float bx = box.left + box.width / 2;
    float by = box.top + box.height / 2;
    float dx = _position.x - bx;
    float dy = _position.y - by;

    if (abs(dy) < box.height / 2) {
        // Side hit
        if (abs(dx) < box.width / 2 + _radius) {
            _velocity.x *= -1;
            return true;
        }
    } else if (abs(dx) < box.width / 2) {
        // Top hit
        if (abs(dy) < box.height / 2 + _radius) {
            _velocity.y *= -1;
            return true;
        }
    } else {
        // Corner hit
        dx -= box.width / 2;
        dy -= box.height / 2;
        if (dx * dx + dy * dy < _radius * _radius) {
            _velocity.x *= -1;
            _velocity.y *= -1;
            return true;
        }
    }
    return false;
}