#include "Brick.hpp"


void Brick::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    if (_hitsLeft < 1) return;
    sf::RectangleShape box({_bounds.width, _bounds.height});
    box.setPosition(_bounds.left, _bounds.top);
    if (_hitsLeft <= 1) box.setFillColor(sf::Color::Red);
    else if (_hitsLeft >= 3) box.setFillColor(sf::Color::Green);
    else box.setFillColor(sf::Color::Yellow);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);
    window.draw(box, states);
}