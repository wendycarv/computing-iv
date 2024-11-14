#include <SFML/Graphics.hpp>
#include <string>
#include "sierpinski.hpp"

int main()
{
    unsigned int size = 600;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(size, size), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear(sf::Color(0x47c7d8FF));
        drawSierpinksi(window, 2, sf::Vector2f(0, size), size);
        window.display();
    }
    return EXIT_SUCCESS;
}