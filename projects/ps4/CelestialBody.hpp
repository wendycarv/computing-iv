// Copyright 2024 Wendy Carvalho
#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody : public sf::Drawable {
 public:
  CelestialBody();
  CelestialBody(double x, double y, double vx, double vy, double mass,
                double radius, std::string imageData)
      : x(x),
        y(y),
        vx(vx),
        vy(vy),
        m(mass),
        fx(0),
        fy(0),
        uRadius(radius),
        imageData(imageData) {
    image.loadFromFile(imageData);
  }

  sf::Vector2f position() {
    return sf::Vector2f(x, y);
  }
  sf::Vector2f velocity() { return sf::Vector2f(vx, vy); }
  float mass() { return m; }
  std::string name() { return imageData; }
  void setNetForce(double fnetx, double fnety);
  void setNewPosition(double pxf, double pyf) {
    x = pxf;
    y = pyf;
  }
  void setNewVelocity(double vxf, double vyf) {
    vx = vxf;
    vy = vyf;
  }
  sf::Vector2f netForce() { return sf::Vector2f(fx, fy); }

  friend std::istream& operator>>(std::istream& input, CelestialBody& b);
  friend std::ostream& operator<<(std::ostream& output, CelestialBody& b);

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  double x;
  double y;
  double vx;
  double vy;
  double m;
  double fx;
  double fy;
  double uRadius;
  std::string imageData;
  sf::Texture image;
};

std::istream& operator>>(std::istream& input, CelestialBody& b);
std::ostream& operator<<(std::ostream& output, CelestialBody& b);
}  // namespace NB
