#pragma once

#include <SFML/Graphics.hpp>

class Brick: public sf::Drawable {
 public:
    Brick(sf::Vector2f pos, sf::Vector2f size, int hits = 3):
        _bounds(pos, size), _hitsLeft(hits) {} 
    sf::FloatRect bounds() const { return _bounds; }

    void hit() { _hitsLeft--; }
    bool isAlive() const { return _hitsLeft > 0; }
 protected:
    void draw(sf::RenderTarget& window, sf::RenderStates states) const override;
 private:
    sf::FloatRect _bounds;
    int _hitsLeft;
};