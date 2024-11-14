#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
    Game game;
    sf::RenderWindow window(sf::VideoMode(game.windowSize().x, game.windowSize().y), "SFML works!");
    window.setPosition({0, 0});

    double stepTimeS = 0.25;

    sf::Clock timer;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        game.changeDirection(Up);
                        break;
                    case sf::Keyboard::A:
                        game.changeDirection(Left);
                        break;
                    case sf::Keyboard::S:
                        game.changeDirection(Down);
                        break;
                    case sf::Keyboard::D:
                        game.changeDirection(Right);
                        break;
                    default: break;
                }
            }
        }

        // TODO : update game
        if (!game.isGameover() && timer.getElapsedTime().asSeconds() >= stepTimeS) {
            game.step();
            timer.restart();
        }

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}