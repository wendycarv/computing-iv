// Copyright 2024 Meriem Elkoudi and Wendy Carvalho

#pragma once
#include <iostream>
#include <string>
#include <vector>

class EDistance {
 public:
     EDistance() {}
     EDistance(std::string s1, std::string s2);
     static int penalty(char a, char b);
     static int min3(int a, int b, int c);
     int optDistance(void);
     std::string alignment(void);
     const std::vector<std::vector<int>>& getMatrix() const { return _matrix; }

 private:
     std::string _s1, _s2;
     std::vector<std::vector<int>> _matrix;
     std::vector<std::vector<int>> _finalMatrix;
};
