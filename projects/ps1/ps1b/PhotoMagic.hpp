// Copyright 2024 Wendy Carvalho

#include "FibLFSR.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace PhotoMagic {
  // transforms image using FibLFSR
  void transform(sf::Image& image, FibLFSR* seed);
}
