// Copyright 2024 Wendy Carvalho and Meriem Elkoudi

#pragma once
#include <SFML/Graphics.hpp>

void pTreeHelper(sf::RenderTarget& window, int N, sf::RectangleShape parent, double angle);
void pTree(sf::RenderTarget& window, double L, int N, sf::Vector2f origin, double angle);
