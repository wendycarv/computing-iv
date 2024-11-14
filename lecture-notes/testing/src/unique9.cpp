#include "unique.hpp"

#include <algorithm>

void uniquify(vector<int>& v) {
    std::sort(v.begin(), v.end());
    auto ptr = std::unique(v.begin(), v.end());
    v.erase(ptr, v.end());
}
