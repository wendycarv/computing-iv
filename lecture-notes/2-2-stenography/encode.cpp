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
    // get the message
    std::cout << "What is your message?" << std::endl;
    std::string message;
    getline(std::cin, message);

    // hide the message in the image
    hideData(image, message);
    // save the new image
    if (!image.saveToFile("hidden.png")) {
        std::cerr << "Failed to save image" << std::endl;
        return 1;
    }
    return 0;
}