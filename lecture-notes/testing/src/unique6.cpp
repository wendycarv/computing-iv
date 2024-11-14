#include "unique.hpp"

#include <algorithm>

void uniquify(vector<int>& v) {
    std::unique(v.begin(), v.end());
}
