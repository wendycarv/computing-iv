#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

int main {
    // load an image
    sf::Image image;
    if (image.loadFromFile("test-pipe-original.png")) {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }

    std:: string message = revealData(image);
    std::cout << message << std::endl;
    return 0;
}