#include "Snake.hpp"

#include <stdexcept>

Direction dirTo(sf::Vector2u start, sf::Vector2u end) {
  if (start.x < end.x) return Direction::Right;
  if (start.x > end.x) return Direction::Left;
  if (start.y < end.y) return Direction::Down;
  if (start.y > end.y) return Direction::Up;
  throw std::invalid_argument("same point");
}

Snake::Snake(sf::Vector2u pos, int numSeg, Direction dir)
    : _facing(dir), _size(numSeg) {
  _textures[Head | Down].loadFromFile("images/head_up.png");
  _textures[Head | Up].loadFromFile("images/head_down.png");
  _textures[Head | Right].loadFromFile("images/head_left.png");
  _textures[Head | Left].loadFromFile("images/head_right.png");
  _textures[Tail | Down].loadFromFile("images/tail_up.png");
  _textures[Tail | Up].loadFromFile("images/tail_down.png");
  _textures[Tail | Right].loadFromFile("images/tail_left.png");
  _textures[Tail | Left].loadFromFile("images/tail_right.png");
  _textures[Left | Right].loadFromFile("images/body_horizontal.png");
  _textures[Up | Down].loadFromFile("images/body_vertical.png");
  _textures[Up | Left].loadFromFile("images/body_topleft.png");
  _textures[Up | Right].loadFromFile("images/body_topright.png");
  _textures[Down | Left].loadFromFile("images/body_bottomleft.png");
  _textures[Down | Right].loadFromFile("images/body_bottomright.png");

  // TODO : Initialize snake
  for (int i = 0; i < numSeg; i++) {
    _positions.push_front(pos);
    switch (dir) {
      case Up:
        pos.y++;
        break;
      case Down:
        pos.y--;
        break;
      case Left:
        pos.x++;
        break;
      case Right:
        pos.x--;
        break;
      default:
        throw std::invalid_argument("doesn't accept head or tail");
    }
  }
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // draw head
  // draw body
  for (size_t i = 1; i < _positions.size() - 1; i++) {
    auto pos = _positions[i];
    Direction prev = dirTo(pos, _positions[i - 1]);
    Direction next = dirTo(pos, _positions[i + 1]);
    sf::Sprite sprite;
sprite.setTexture(_textures.at(prev|next]);
sprite.setPosition(pos.x*TILE_SIZE, pos.y*TILE_SIZE);
target.draw(sprite, states);
  }
}

bool Snake::step() {
  // TODO : move snake one position
  // compute next head
  switch (_facing) {
    case Up:
      head.y--;
      break;
    case Down:
      head.y++;
      break;
    case Left:
      head.x--;
      break;
    case Right:
      head.x++;
    default:
      throw std::runtime_error("Invalid facing");
  }
  // add to front
  _positions.push_front(head);
  // remove tail
  if (_positions.size() > _size) {
    _positions.pop_back();
  }
  // check for self-collision
  return std::find(_positions.begin() + 1, _positions.end(), head) !=
         _positions.end();
  return false;  // TODO : determine if snake is alive
}
