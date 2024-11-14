#include "Concordance.hpp"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>

Concordance::Concordance(const std::string& filename) {
    std::ifstream is(filename);
    if (!is.is_open()) throw std::ios_base::failure("Unable to open file");

    while (!is.eof()) {
        std::string verse;
        std::getline(is, verse);
        std::stringstream ss(verse);
        while (!ss.eof()) {
            std::string word;
            ss >> word;
            // Strip punctuation
            _table[word].insert(_verses.size());
        }
        _verses.push_back(verse);
    }
}

std::vector<std::string> Concordance::getVerses(const std::string & word) const {
    std::vector<std::string> result;
    if (!_table.count(word)) return result;
    const std::set<size_t>& indices = _table.at(word);
    std::transform(indices.begin(), indices.end(), std::back_inserter(result),
        [this](size_t i) { return std::to_string(i + 1) + _verses[i]; }
    );
    return result;
}

std::vector<std::string> Concordance::getVerses(const std::vector<std::string> & words) const {
    std::vector<std::string> result;
    if (!_table.count(words.front())) return result;
    std::set<size_t> indices = _table.at(words.front());
    for (const auto& w : words) {
        if (!_table.count(w)) return result;
        const std::set<size_t> is = _table.at(w);
        std::set<size_t> copy;
        std::set_intersection(
            indices.begin(), indices.end(),
            is.begin(), is.end(),
            std::inserter(copy, copy.end())
        );
        indices = std::move(copy);
    }
    std::transform(indices.begin(), indices.end(), std::back_inserter(result),
        [this](size_t i) { return std::to_string(i + 1) + _verses[i]; }
    );
    return result;
}