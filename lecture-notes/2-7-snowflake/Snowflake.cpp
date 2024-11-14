#include "Snowflake.hpp"
#include <cmath>

const double DEG_PER_RAD = 180 / M_PI;

void drawHelper(sf::RenderTarget& window, int n, sf::Vector2f center, double radius, double angleDeg){
    if (n < 0) return;

    sf::CircleShape triangle(radius, 3);
    triangle.setOrigin(sf::Vector2f(radius, radius));
    triangle.setPosition(center);
    triangle.rotate(angleDeg);
    triangle.setFillColor(sf::Color::White);
    window.draw(triangle);

    for (int i = -1; i <= 1; i++) {
        double thetaDeg = angleDeg +120 * i;
        double thetaRad = thetaDeg / DEG_PER_RAD;
        sf::Vector2f childPt = center;
        double distance = radius * 1.25;
        childPt.x += distance * sin(thetaRad);
        childPt.y -= distance * cos(thetaRad);
        drawHelper(window, n - 1, childPt, radius/2, thetaDeg);
    }
}

void drawSnowflake(sf::RenderTarget& window, int n, sf::Vector2f origin, double size) {
    double radius = size / sqrt(3);
    for (int i = 0; i < 6; i++) {
        double thetaDeg = 60 * i;
        double thetaRad = thetaDeg / DEG_PER_RAD;
        sf::CircleShape triangle(radius, 3);
        triangle.setOrigin(radius, radius);
        sf::Vector2f pt = origin;
        pt.x += 2 * radius *sin(thetaRad);
        pt.y -= 2 * radius *cos(thetaRad);
        triangle.setPosition(pt);
        triangle.setFillColor(sf::Color::Cyan);
        triangle.rotate(thetaDeg);
        window.draw(triangle);

        sf::Vector2f childPt = pt;
        double distance = radius * 1.25;
        childPt.x += distance * sin(thetaRad);
        childPt.y -= distance * cos(thetaRad);
        drawHelper(window, n - 1, childPt, radius/2, thetaDeg);
    }
}