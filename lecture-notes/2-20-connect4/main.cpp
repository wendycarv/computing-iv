#include <SFML/Graphics.hpp>

#include "connect4.hpp"

int main()
{
    Connect4 game;
    sf::RenderWindow window(sf::VideoMode(game.windowSize().x, game.windowSize().y), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (!game.isOver()) {
                    int x = event.mouseButton.x / TILE_SIZE;
                    game.dropPiece(x);
                }
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(game);
        window.display();
    }

    return 0;
}