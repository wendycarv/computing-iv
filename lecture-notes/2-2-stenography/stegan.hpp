#pragma once

#include <string>
#include <SFML/Graphics.hpp>

void hideData(sf::Image& image, const std::string& msg);
std::string revealData(sf::Image& image);