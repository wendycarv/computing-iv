#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Concordance {
 public:
    Concordance(const std::string& filename);

    std::vector<std::string> getVerses(const std::string & word) const;
    std::vector<std::string> getVerses(const std::vector<std::string> & words) const;
 private:
    std::vector<std::string> _verses;
    std::unordered_map<std::string, std::set<size_t>> _table;
};
