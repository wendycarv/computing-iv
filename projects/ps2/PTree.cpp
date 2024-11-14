// Copyright 2024 Wendy Carvalho and Meriem Elkoudi

#include "PTree.hpp"

#include <cmath>
#include <iostream>

const double DEG_PER_RAD = 180 / M_PI;

void pTreeHelper(sf::RenderTarget& window, int N, sf::RectangleShape parent,
                 double angle) {
  window.draw(parent);

  if (N < 1) return;

  // new length will be parent's length * cos(45)
  // left length first
  auto newLength = parent.getSize().x * cos(45 / DEG_PER_RAD);
  auto leftLength = parent.getSize().x * cos(angle / DEG_PER_RAD);
  auto rightLength = parent.getSize().x * sin(angle / DEG_PER_RAD);
  sf::Vector2f leftCLength(leftLength, leftLength);
  sf::Vector2f rightCLength(rightLength, rightLength);
  sf::Vector2f childLength(newLength, newLength);

  // left children
  sf::RectangleShape leftChild = parent;
  // new length is parent's length * cos 45
  leftChild.setSize(leftCLength);
  leftChild.setOrigin(0, leftChild.getSize().y);
  // set new child's position based on parent's previous transformations
  // set to top left vertex
  leftChild.setPosition(parent.getTransform().transformPoint({0, 0}));
  leftChild.rotate(-angle);
  // color manipulation (adding only green and blue component for "leaves")
  sf::Color newColor = leftChild.getFillColor();
  newColor += sf::Color(6, 15, 12);
  leftChild.setFillColor(newColor);
  pTreeHelper(window, N - 1, leftChild, angle);

  // right children
  sf::RectangleShape rightChild = parent;
  rightChild.setSize(rightCLength);
  rightChild.setOrigin(rightChild.getSize());

  // set new child's position based on parent's previous transformations
  // set to top right vertex
  rightChild.setPosition(
      parent.getTransform().transformPoint({parent.getSize().x, 0}));
  rightChild.rotate(90 - angle);
  // right side color manipulation
  rightChild.setFillColor(newColor);
  pTreeHelper(window, N - 1, rightChild, angle);
}

void pTree(sf::RenderTarget& window, double L, int N, sf::Vector2f origin,
           double angle) {
  sf::RectangleShape square(sf::Vector2f(L, L));
  sf::Vector2f pt = origin;
  square.setOrigin(L / 2, L / 2);
  pt.y += (3 * L) / 2;

  if (L > 200) {
    double scale = (1 / L) * 200;
    square.setScale(scale, scale);
    // centering on x axis and keeping at bottom of y axis
    pt.y = window.getSize().y - L / 4;
    pt.x = window.getSize().x / 2.f;
  }

  square.setPosition(pt);

  square.setFillColor(sf::Color(0x663b2dff));
  pTreeHelper(window, N, square, angle);
}
