// Copyright 2024 Wendy Carvalho

#include <iostream>

#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

int main() {
  std::string seed_input, image_input, image_output;
  sf::Image image;
  sf::Texture texture1, texture2;
  sf::Sprite sprite1, sprite2;

  std::cin >> image_input >> image_output >> seed_input;

  PhotoMagic::FibLFSR seed(seed_input);

  if (!image.loadFromFile(image_input)) {
    std::cerr << "failed to open the image" << std::endl;
    return -1;
  }

  texture1.loadFromImage(image);
  sprite1.setTexture(texture1);

  // encode
  transform(image, &seed);
  sf::Vector2u size = image.getSize();

  sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Raw Cat");
  sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Baked Cat");

  texture2.loadFromImage(image);
  sprite2.setTexture(texture2);

  while (window1.isOpen() && window2.isOpen()) {
    sf::Event event;
    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window1.close();
    }
    while (window2.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window2.close();
    }

    window1.clear();
    window1.draw(sprite1);
    window1.display();
    window2.clear();
    window2.draw(sprite2);
    window2.display();
  }

  // write the file
  if (!image.saveToFile(image_output))
    std::cerr << "failed to save the image" << std::endl;

  return 0;
}
