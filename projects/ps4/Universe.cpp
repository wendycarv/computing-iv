// Copyright 2024 Wendy Carvalho

#include <cmath>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Universe.hpp"

namespace NB {

Universe::Universe() {
  n = 0;
  r = 0.0;
}

Universe::Universe(std::string fileName) {
  std::ifstream file;
  file.open(fileName);

  file >> *this;
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& cb : celestialBodies) {
    target.draw(*cb, states);
  }
}

CelestialBody& Universe::operator[](size_t index) {
  return *celestialBodies.at(index);
}

void Universe::step(double seconds) {
  const double G = 6.67e-11;
  // calculating particle's new position
  for (int i = 0; i < numParticles(); i++) {
    double fx = 0;
    double fy = 0;
    for (int j = 0; j < numParticles(); j++) {
      if (i != j) {
        // calculate net force using current time t, universal gravitation, and
        // superposition
        double dx = celestialBodies.at(j)->position().x -
                    celestialBodies.at(i)->position().x;
        double dy = celestialBodies.at(j)->position().y -
                    celestialBodies.at(i)->position().y;
        double distance = sqrt((dx * dx) + (dy * dy));
        double fnet = (G * celestialBodies.at(i)->mass() *
                       celestialBodies.at(j)->mass()) /
                      (distance * distance);
        fx += fnet * (dx / distance);
        fy += fnet * (dy / distance);
      }
    }
    celestialBodies.at(i)->setNetForce(fx, fy);
  }
  for (auto& each : celestialBodies) {
     // calculate acceleration at a time t using net force
    double ax =
        each->netForce().x / each->mass();
    double ay =
        each->netForce().y / each->mass();
    // calculate new v at the next time step by using a and old v
    double vxf = each->velocity().x + (seconds * ax);
    double vyf = each->velocity().y + (seconds * ay);
    // calculate new position at time t + dt by using new velocity and old pos
    // (px + dt*vx, py+dt*vy)
    double pxf = each->position().x + (seconds * vxf);
    double pyf = each->position().y + (seconds * vyf);
    each->setNewPosition(pxf, pyf);
    each->setNewVelocity(vxf, vyf);
  }
}

std::istream& operator>>(std::istream& input, NB::Universe& u) {
  input >> u.n;
  input.ignore();
  input >> u.r;

  float x, y, vx, vy, mass;
  std::string imageName;

  // while there are still lines w planet info
  while (input >> x >> y >> vx >> vy >> mass >> imageName) {
    auto body =
        std::make_shared<CelestialBody>(x, y, vx, vy, mass, u.r, imageName);
    u.celestialBodies.push_back(body);
  }
  return input;
}

std::ostream& operator<<(std::ostream& output, NB::Universe& u) {
  output << u.n << "\n" << u.r << std::endl;
  for (auto& body : u.celestialBodies) {
    output << body->position().x << " " << body->position().y << " "
           << body->velocity().x << " " << body->velocity().y << " "
           << body->mass() << " " << body->name() << std::endl;
  }
  return output;
}

}  // namespace NB
