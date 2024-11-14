// Copyright 2024 Wendy Carvalho

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "CelestialBody.hpp"

namespace NB {
CelestialBody::CelestialBody() {
  x = 0;
  y = 0;
  vx = 0;
  vy = 0;
  m = 0;
  imageData = "";
}

void CelestialBody::setNetForce(double fnetx, double fnety) {
  fx = fnetx;
  fy = fnety;
}

void CelestialBody::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const {
  double ratio = (2 * uRadius) / target.getSize().x;
  sf::Sprite cb;
  cb.setTexture(image);
  cb.setPosition(x / ratio, -y / ratio);
  target.draw(cb, states);
}

std::istream& operator>>(std::istream& input, CelestialBody& b) {
  input >> b.x;
  input >> b.y;
  input >> b.vx;
  input >> b.vy;
  input >> b.m;
  input >> b.imageData;
  return input;
}
std::ostream& operator<<(std::ostream& output, CelestialBody& b) {
  output << b.x << " ";
  output << b.y << " ";
  output << b.vx << " ";
  output << b.vy << " ";
  output << b.m << " ";
  output << b.imageData << " ";

  return output;
}
};  // namespace NB
