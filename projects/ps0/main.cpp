// Copyright 2024 Wendy Carvalho

#include <SFML/Graphics.hpp>

int main() {
  // sets up window, title, and size
  sf::RenderWindow window(sf::VideoMode(700, 700), "SFML works!");
  window.setVerticalSyncEnabled(true);

  // how fast things are moving
  window.setFramerateLimit(5);

  // green circle
  sf::CircleShape shape(100.f);
  shape.setPosition(250, 100);
  shape.setFillColor(sf::Color::Green);

  // set up alien image
  sf::Texture sprite_1;
  if (!sprite_1.loadFromFile("sprite.png"))
    return EXIT_FAILURE;
  sf::Sprite sprite(sprite_1);

  // define initial sprite position
  float yPosition = 0.0f;
  int newX = 350;
  int newY = 200;

  // left mouse click initially false
  bool mouseClicked = false;

  // set up laser facing left
  sf::Texture sprite_2;
  if (!sprite_2.loadFromFile("laser_left.png"))
    return EXIT_FAILURE;
  sf::Sprite spriteLaserLeft(sprite_2);

  // set up laser facing right
  sf::Texture sprite_3;
  if (!sprite_3.loadFromFile("laser_right.png"))
    return EXIT_FAILURE;
  sf::Sprite spriteLaserRight(sprite_3);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // mechanism for alien bobbing up and down
    if (yPosition == 2)
      yPosition -= 2;
    else
      yPosition += 2;

    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
      if (sprite.getScale().x != 1) {
        sprite.setScale(1, 1);
        sprite.setPosition(newX-100, newY);
      }
      newX += -20;
      sprite.move(newX, 0.0f);
    }

    // move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      if (sprite.getScale().x != -1) {
        sprite.setScale(-1, 1);
        sprite.setPosition(newX+100, newY);
      }
      newX += 20;
      sprite.move(newX, 0.0f);
    }

    // move up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      newY += -20;
      sprite.move(0.0f, newY);
    }

    // move down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
      newY += 20;
      sprite.move(0.0f, newY);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      mouseClicked = true;
      if (sprite.getScale().x == 1)
        spriteLaserLeft.setPosition(newX+100, newY+50);
      else
        spriteLaserRight.setPosition(newX-100, newY+50);
    }

    // update alien position (bobbing)
    sprite.setPosition(newX, newY+yPosition);

    // defines laser beam direction based on that of alien sprite
    if (sprite.getScale().x == 1)
      spriteLaserLeft.move(-100.0f, 0);
    else
      spriteLaserRight.move(100.0f, 0);

    window.clear();
    window.draw(shape);
    window.draw(sprite);

    if (mouseClicked) {
      if (sprite.getScale().x == 1)
        window.draw(spriteLaserLeft);
      else
        window.draw(spriteLaserRight);
    }

    window.display();
  }

  return 0;
}
