#include "Snowflake.hpp"

int main() {
    double length = 300;
    unsigned int size = 600;

      // Create the main window
  sf::RenderWindow window(sf::VideoMode(size, size), "SFML window");

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed) window.close();
    }
    // Clear screen
    window.clear(sf::Color::Black);
    drawSnowflake(window, 3,sf::Vector2f(size / 2, size / 2), length);
    window.display();
  }
    
}