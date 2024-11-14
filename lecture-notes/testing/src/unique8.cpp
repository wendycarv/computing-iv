#include "unique.hpp"

#include <algorithm>

void uniquify(vector<int>& v) {
    auto ptr = std::unique(v.begin(), v.end());
    v.erase(ptr, v.end());
}
