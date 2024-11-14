#include "unique.hpp"

void uniquify(vector<int>& v) {
    for (auto iter = v.begin(); iter < v.end() - 1; iter++) {
        if (*iter == *(iter + 1)) {
            v.erase(iter);
        }
    }
}
