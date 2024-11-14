#pragma once

#include <string>
#include <vector>

class Brainfuck {
  public:
    Brainfuck(const std::string& prog);
    Brainfuck(std::istream& pfile);

    void run(std::istream& in, std::ostream& out);

    int _bp;
    std::string _program;
    std::vector<char> _buffer;
    size_t _bp;
};