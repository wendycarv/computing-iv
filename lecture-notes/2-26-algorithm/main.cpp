#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

template<typename T>
T sumOfSquares(const T &sum, const T& elem) {
sum = 0;
sum += pow(elem, 2);
}

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  int a[] = {1, 2, 3, 4, 5};
  std::vector<std::string> words = {"hello", "world"};
  std::cout << std::accumulate(v.begin(), v.end(), 0) << std::endl;
  std::cout << std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>()) << std::endl;
  std::cout << std::accumulate(v.begin(), v.end(), 0, sumOfSquares<int>) << std::endl;
  std::cout << std::accumulate(v.begin(), v.end(), 0, [](auto sum)) << std::endl;
  std::cout << std::accumulate(v.begin() + 1, v.end() -1, 100) << std::endl;
  std::cout << std::accumulate(words.begin(), words.end(), std::string())
            << std::endl;

  std::cout << std::accumulate(a, a+5, 0) << std::endl;
}