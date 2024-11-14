#include "unique.hpp"

#include <algorithm>

void uniquify(vector<int>& v) {
    std::sort(v.begin(), v.end());
    std::unique(v.begin(), v.end());
}
