#include <SFML/Graphics.hpp>

#include "Minesweeper.hpp"

int main() {
    size_t width = 20;
    size_t height = 15;
    size_t mines = 10;

    Minesweeper game(height, width, mines);

    sf::RenderWindow window(sf::VideoMode(game.pixelWidth(), game.pixelHeight()), "SFML works!");
    window.setPosition({0, 0});

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                unsigned int x = event.mouseButton.x / Minesweeper::TILE_SIZE;
                unsigned int y = event.mouseButton.y / Minesweeper::TILE_SIZE;
                game.click(x,y);
            }
        }

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}