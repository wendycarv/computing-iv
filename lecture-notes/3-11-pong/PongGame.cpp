#include <SFML/Graphics.hpp>

#include "Pong.hpp"

int main()
{
    Pong game({800, 600});
    sf::RenderWindow window(sf::VideoMode(game.windowSize().x, game.windowSize().y), "SFML works!");
    window.setPosition({0, 0});

    sf::Clock timer;
    sf::Time lastTime = timer.getElapsedTime();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    
                    default: break;
                }
            }
        }

        sf::Time now = timer.getElapsedTime();
        sf::Time delta = now - lastTime;
        lastTime = now;
        game.step(delta.asSeconds());

        window.clear();
        window.draw(game);
        window.display();
    }

    return 0;
}