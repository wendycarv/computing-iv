// Copyright 2024 Wendy Carvalho

#include "PhotoMagic.hpp"

void PhotoMagic::transform(sf::Image& image, FibLFSR* seed) {
  sf::Color p;

  // get size of image
  sf::Vector2u size = image.getSize();
  unsigned x, y;
  // use LFSR to transform the image:
  // for each pixel (x,y) in row major order [(0,0),(0,1)...]
  // extract the red, green, and blue components of the color
  // (each component is an int 0-255)
  for (x = 0; x < size.x; x++) {
    for (y = 0; y < size.y; y++) {
      p = image.getPixel(x, y);

      // xor each color component with a newly generated 8-bit integer
      // create a new color using the result of the XOR operations
      p.r ^= seed->generate(8);
      p.g ^= seed->generate(8);
      p.b ^= seed->generate(8);

      // set the pixel in the new picture to that color
      image.setPixel(x, y, p);
    }
  }
}
