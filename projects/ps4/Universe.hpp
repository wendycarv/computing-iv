// Copyright 2024 Wendy Carvalho
#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {
class Universe : public sf::Drawable {
 public:
  Universe();
  explicit Universe(std::string fileName);

  int numParticles() { return n; }
  double radius() { return r; }
  void step(const double seconds);

  friend std::istream& operator>>(std::istream& input, Universe& u);
  friend std::ostream& operator<<(std::ostream& output, Universe& u);
  CelestialBody& operator[](size_t index);

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  int n;
  double r;
  std::vector<std::shared_ptr<CelestialBody>> celestialBodies;
};
std::istream& operator>>(std::istream& input, Universe& u);
std::ostream& operator<<(std::ostream& output, Universe& u);
};  // namespace NB
