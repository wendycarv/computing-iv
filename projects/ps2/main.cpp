// Copyright 2024 Wendy Carvalho and Meriem Elkoudi

#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PTree.hpp"

int main() {
  // length of base
  double L;
  double A;
  // depth of recursion
  int N;
  std::cin >> L >> N >> A;

  // what does it mean to make sure default is 45?

  int width = L * 8;
  int height = L * 5;
  // int size = 600;
  //  Create the main window
  sf::RenderWindow window(sf::VideoMode(width, height), "The Glorious Tree");

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed) window.close();
    }
    // Clear screen
    window.clear(sf::Color::Black);
    if (A == 45) {
      pTree(window, L, N, sf::Vector2f(width / 2, height / 2 + L / 2), A);
    } else if (A < 45) {
      pTree(window, L, N, sf::Vector2f(width - width / 3, height / 2), A);
      window.setSize(sf::Vector2u(width + width / 2, height + height / 2));
    } else if (A > 45) {
      pTree(window, L, N, sf::Vector2f(width / 3, height / 2 + L / 2), A);
      window.setSize(sf::Vector2u(width + width / 2, height + height / 2));
    }
    window.display();
  }
  return EXIT_SUCCESS;
}
