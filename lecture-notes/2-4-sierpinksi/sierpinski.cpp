#include "sierpinski.hpp"

#include <cmath>


void drawSierpinksi(sf::RenderTarget& window,int n, sf::Vector2f top,sf::Vector2f left, sf::Vector2f right) {
    if (n == 0) {
        sf::ConvexShape triangle(3);
        triangle.setPoint(0, top);
        triangle.setPoint(1, right);
        triangle.setPoint(2, left);
        triangle.setFillColor(sf::Color(0xc69c1FF));
        window.draw(triangle);
    } else {
        sf::Vector2f topLeft = { (top.x + left.x) / 2, (top.y +left.y) / 2};
        sf::Vector2f topRight = { (top.x + right.x) / 2, (top.y +right.y) /2};
        sf::Vector2f bottom = { (left.x + right.x) / 2, (left.y +right.y) /2};
        drawSierpinksi(window, n - 1, top, topLeft, topRight);
        drawSierpinksi(window, n - 1, topLeft, left, bottom);
        drawSierpinksi(window, n - 1, topRight, bottom, right);
    }

}

void drawSierpinksi(sf::RenderTarget& window, int n, sf::Vector2f left, float size) {
    float height = size * std::sqrt(3)/2;
    left.y -= (size - height) / 2;
    sf::Vector2f top = {left.x+size / 2,left.y-height};
    sf::Vector2f right ={left.x+size,left.y};
    drawSierpinksi(window, n, top, left, right);
}