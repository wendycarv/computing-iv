#include "connect4.hpp"

#include <algorithm>

const size_t WIN_NUM = 4;

Connect4::Connect4(size_t w, size_t h):
        _nextPlayer(Red), _width(w), _height(h), _grid(w)
{
    _redTexture.loadFromFile("redpawn.png");
    _blackTexture.loadFromFile("blackpawn.png");
    //_grid[3].push_back(Red);
    //_grid[3].push_back(Black);
    //_grid[2].push_back(Red);
}

void Connect4::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(size_t x = 0; x < _width; x++) {
        for (size_t y = 0; y < _height; y++) {
            if(y < _grid[x].size()) {
                sf::Sprite disc(_grid[x][y] == Red ? _redTexture : _blackTexture);
                disc.setPosition(x * TILE_SIZE, (_height - y - 1) * TILE_SIZE);
                target.draw(disc, states);
            } else {
                sf::CircleShape disc(TILE_SIZE/2);
                disc.setFillColor(sf::Color(0xAAAAFFAA));
                disc.setPosition(x * TILE_SIZE, (_height - y - 1) * TILE_SIZE);
                target.draw(disc, states);
            }
        }
    }
}

void Connect4::dropPiece(int col) {
    if (_grid[col].size() < _height) { // if we have space we can do stuff
        _grid[col].push_back(_nextPlayer);
        _nextPlayer = _nextPlayer == Red ? Black : Red;
    }
}

bool Connect4::isOver() const {
    for (size_t x = 0; x < _width; x++) {
        for (size_t y = 0; y < _grid[x].size(); y++) {
            // horizontal
            if (doesWinAtPoint(sf::Vector2i(x,y), {1, 0})) return true;
            // vertical
            if (doesWinAtPoint(sf::Vector2i(x,y), {0, 1})) return true;
            // diagonal - rising
            if (doesWinAtPoint(sf::Vector2i(x,y), {1, 1})) return true;
            // diagonal - falling
            if (doesWinAtPoint(sf::Vector2i(x,y), {1, -1})) return true;
        }
    }
    return false;
}

bool Connect4::doesWinAtPoint(sf::Vector2i pt, sf::Vector2i qt) const {
    Player color = _grid[pt.x][pt.y];
    for (size_t i = 1; i < WIN_NUM; i++) {
        pt += qt;
        if(_grid[pt.x].size() < (unsigned int)pt.y || _grid[pt.x][pt.y] != color) { // if the col here is shorter than grid
            return false;
        }
    }
    return true;
}
