#include "Game.hpp"

#include <chrono>

Game::Game(unsigned int width, unsigned int height):
        _gameover(false),
        _snake({width / 2, height / 2}, 3, Direction::Down),
        _size(width, height),
        _gen(std::chrono::system_clock::now().time_since_epoch().count())
{
    _appleTexture.loadFromFile("images/apple.png");
    _applePos = randPos();
}


sf::Vector2u Game::randPos() {
    std::uniform_int_distribution<unsigned int> xrange(0, _size.x - 1);
    std::uniform_int_distribution<unsigned int> yrange(0, _size.y - 1);
    return sf::Vector2u(xrange(_gen), yrange(_gen)); // TODO
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // TODO : draw snake and apple
    sf::Sprite apple;
    apple.setTexture(_appleTexture);
    apple.setPosition(_applePos.x * TILE_SIZE, _applePos.y * TILE_SIZE);
    target.draw(apple, states);
    target.draw(_snake, states);
}


void Game::step() {
    // move snake
    if (_snake.step()) {
        _gameover = true;
    }
    // eat apple
    if (head == _applePos) {
        _snake.chomp();
        _applePos = randPos();
    }
    // collide 
    if (head.x >= _size.x || head.y >= _size.y) {
        _gameover = true;
    }
}

