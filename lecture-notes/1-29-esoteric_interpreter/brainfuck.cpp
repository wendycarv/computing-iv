
#include "brainfuck.hpp"
#include <unordered_map>

std::string getString(std::istream& pfile) {
  std::string str;
  getline(pfile, str, '\0');
  return str;
}

Brainfuck::Brainfuck(const std::string& prog): _program(prog), _buffer(1024, 0), _bp(0) {}

Brainfuck::Brainfuck(std::istream& pfile):Brainfuck(getString(pfile)) {}

void Brainfuck::run(std::istream& in, std::ostream& out) {
  std::vector<size_t> lbrackets;
  std::vector<size_t> rbrackets;
    // now we need a lookup table (hash-based would be faster)
  std::unordered_map<size_t, size_t> jumpTable;
  for (size_t i = 0; i < _program.size();i++) {
    if (_program[i] == '[') {
      lbrackets.push_back(i);
    } else if (_program[i] == ']') {
      // rbrackets.push_back(i);
      jumpTable[lbrackets.back()] = i;
      jumpTable[i] = lbrackets.back();
    }
  }


  // for each token in program
  for (size_t ip = 0; ip < _program.size(); ip++) {
  // execute token
    char token = _program[ip];
    switch (token) {
      case '+':
        _buffer[_bp]++;
        break;
      case '-':
        _buffer[_bp]--;
        break;
      case '>':
        _bp++;
        if (_bp >= _buffer.size()) _buffer.push_back(0);
        break;
      case '<':
        if (_bp) _bp--;
        break;
      case '.':
        out << _buffer[_bp];
        break;
      case ',':
      in >> _buffer[_bp];
      case '[':
        if(!_buffer[_bp]) {
          ip = jumpTable[ip];
        }
        break;
        // increase on [
        // decrease on ]
        // stop on 0
      case ']':
        if(!_buffer[_bp]) {
          ip = jumpTable[ip];
        }
    }
  }

}