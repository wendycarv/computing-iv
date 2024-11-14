// Copyright 2024  Wendy Carvalho
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Sokoban.hpp"

int main(int argc, char *argv[]) {
  std::ifstream lvlFile;

  SB::Sokoban game;
  lvlFile.open(argv[1]);
  lvlFile >> game;

  sf::Clock clock;
  sf::Text timeText, final, victoryText;
  std::string str;
  sf::Time timeElapsed;
  int seconds, minutes = 0;

  size_t width = game.width() * game.TILE_SIZE;
  size_t height = game.height() * game.TILE_SIZE;

  sf::RenderWindow window(sf::VideoMode(width, height), "Sokoban");
  window.setPosition({0, 0});

  sf::Font font;
  font.loadFromFile("Arial.ttf");

  sf::Music music;
  if (!music.openFromFile("bgmusic.wav")) {
    return -1;
  }
  music.play();

  while (window.isOpen()) {
    sf::Event event;

    if (!game.isWon()) {
      timeElapsed = clock.getElapsedTime();
      seconds = static_cast<int>(timeElapsed.asSeconds());
      str = "Time: " + std::to_string(minutes) + ":" + std::to_string(seconds);

      if (seconds < 10 && minutes < 10) {
        str =
            "0" + std::to_string(minutes) + ":" + "0" + std::to_string(seconds);
      } else if (seconds >= 10 && minutes < 10) {
        str = "0" + std::to_string(minutes) + ":" + std::to_string(seconds);
      } else if (seconds < 10 && minutes >= 10) {
        str = std::to_string(minutes) + ":" + "0" + std::to_string(seconds);
      } else {
        str = std::to_string(minutes) + ":" + std::to_string(seconds);
      }
      if (seconds == 60) {
        minutes++;
        clock.restart();
      }
    }
    timeText.setFont(font);
    timeText.setString(str);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed) {
        if (!game.isWon()) {
          switch (event.key.code) {
            case sf::Keyboard::W:
              game.movePlayer(SB::Up);
              break;
            case sf::Keyboard::A:
              game.movePlayer(SB::Left);
              break;
            case sf::Keyboard::S:
              game.movePlayer(SB::Down);
              break;
            case sf::Keyboard::D:
              game.movePlayer(SB::Right);
              break;
            case sf::Keyboard::Up:
              game.movePlayer(SB::Up);
              break;
            case sf::Keyboard::Left:
              game.movePlayer(SB::Left);
              break;
            case sf::Keyboard::Down:
              game.movePlayer(SB::Down);
              break;
            case sf::Keyboard::Right:
              game.movePlayer(SB::Right);
              break;
            default:
              break;
          }
        }
        switch (event.key.code) {
          case sf::Keyboard::R:
            lvlFile.clear();
            lvlFile.seekg(0);
            game.resetBoxes();
            lvlFile >> game;
            clock.restart();
            minutes = seconds = 0;
            break;
          case sf::Keyboard::Z:
            game.undo();
          default:
            break;
        }
      }
    }

    window.clear();
    window.draw(game);

    if (game.isWon()) {
      // victory!!
      std::string finalTime = str;
      final = timeText;
      final.setString(finalTime);
      victoryText.setFont(font);
      victoryText.setString("You win!");
      victoryText.setCharacterSize(50);
      sf::FloatRect textRect = victoryText.getLocalBounds();
      victoryText.setFillColor(sf::Color::White);
      victoryText.setStyle(sf::Text::Bold);
      victoryText.setOrigin(textRect.left + textRect.width / 2.0f,
                            textRect.top + textRect.height / 2.0f);
      victoryText.setPosition(width / 2.0f, height / 2.0f);

      music.stop();
      if (!game.soundIsPlaying()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("victory.wav")) return -1;
        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.play();
        game.setPlayingTrue();
        while (sound.getStatus() == sf::Sound::Playing) {
        }
      }

      window.draw(victoryText);
      window.draw(final);
    } else {
      window.draw(timeText);
    }
    window.display();
  }
}
