#include "unique.hpp"

#include <iostream>

void uniquify(vector<int>& v) {
    for (auto iter = v.begin(); iter + 1 < v.end(); iter++) {
        for (auto iter2 = iter + 1; iter2 < v.end(); iter2++) {
            if (iter == iter2) {
                v.erase(iter2);
            }
        }
    }
}
