#pragma once

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable {
 public:
    Paddle(sf::Vector2f pos, sf::Vector2f size):
        _position(pos), _size(size) {}
    void move(sf::Vector2f vel, float dtsec);
    sf::FloatRect bounds() const;
 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
 private:
    sf::Vector2f _position;
    sf::Vector2f _size;
};
