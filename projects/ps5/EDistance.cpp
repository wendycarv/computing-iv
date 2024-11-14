// Copyright 2024 Meriem Elkoudi and Wendy Carvalho
#include <algorithm>
#include <sstream>
#include "EDistance.hpp"

EDistance::EDistance(std::string s1, std::string s2) : _s1(s1), _s2(s2) {
  // allocates data structures
  // n * m
  // std::vector<int> v1;
  _matrix.resize(s1.length() + 1, std::vector<int>(s2.length() + 1));
  for (unsigned int i = 0; i < s1.length() - 1; i++) {
    for (unsigned int j = 0; j < s2.length() - 1; j++) {
      _matrix[i][j] = 0;
    }
  }
}

int EDistance::penalty(char a, char b) {
  if (a == b) {
    return 0;
  } else {
    if (a == ' ' || b == ' ') {
      return 2;
    } else {
      return 1;
    }
  }
}

int EDistance::min3(int a, int b, int c) { return std::min(std::min(a, b), c); }

int EDistance::optDistance(void) {
  // opt[i][j] = min{ opt[i+1][j+1] + 0/1, opt[i+1][j] + 2, opt[i][j+1] + 2 }
  int match, del, insert;
  int rowSize = _matrix.size();
  int colSize = _matrix[0].size();
  for (int i = 0; i < rowSize; i++) {
    _matrix[i][0] = i * 2;
  }
  for (int j = 0; j < colSize; j++) {
    _matrix[0][j] = j * 2;
  }
  for (int i = 1; i < rowSize; i++) {
    for (int j = 1; j < colSize; j++) {
      match = _matrix[i - 1][j - 1] + penalty(_s1[i - 1], _s2[j - 1]);
      del = _matrix[i - 1][j] + 2;
      insert = _matrix[i][j - 1] + 2;
      _matrix[i][j] = min3(match, del, insert);
    }
  }

    // for (int i = 0; i < rowSize; i++) {
    //   for (int j = 0; j < colSize; j++) {
    //     std::cout << _matrix[i][j] << " ";
    //   }
    //   std::cout << "\n";
    // }
  // std::cout << _matrix[rowSize - 1][colSize - 1];
  return _matrix[rowSize - 1][colSize - 1];
}

std::string EDistance::alignment(void) {
  std::string a = "";
  std::string b = "";
  std::string str = "";

  int i = _matrix.size() - 1;
  int j = _matrix[0].size() - 1;

  while (i > 0 || j > 0) {
    if (i > 0 && j > 0 &&
        _matrix[i][j] ==
            _matrix[i - 1][j - 1] + penalty(_s1[i - 1], _s2[j - 1])) {
      str = "\n" + std::string(1, _s1[i - 1]) + " " +
            std::string(1, _s2[j - 1]) + " " +
            std::to_string(_matrix[i][j] - _matrix[i - 1][j - 1]) + str;
      i--;
      j--;
    } else if (i > 0 && _matrix[i][j] == _matrix[i - 1][j] + 2) {
      str = "\n" + std::string(1, _s1[i - 1]) + " -" + +" " +
            std::to_string(_matrix[i][j] - _matrix[i - 1][j]) + str;
      i--;
    } else {
      str = "\n- " + std::string(1, _s2[j - 1]) + " " +
            std::to_string(_matrix[i][j] - _matrix[i][j - 1]) + str;
      j--;
    }
  }
  // removing first '\n' at beginning
  str = str.substr(1, str.size() - 1);
  // std::cout << str << std::endl;
  return str;
}
