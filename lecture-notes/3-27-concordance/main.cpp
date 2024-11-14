#include <iostream>
#include <sstream>
#include <string>

#include "Concordance.hpp"

bool isDone() {
    std::cout << "Do you want to continue?" << std::flush;
    std::string response;
    getline(std::cin, response);
    return tolower(response[0]) != 'y';
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
        return 0;
    }
    // Open the file
    // Prepare the concordance
    Concordance concord(argv[1]);
    do {
        // Ask for a word
        std::cout << "What do you want to search for? " << std::flush;
        std::string query;
        getline(std::cin, query);
        std::vector<std::string> words;
        std::stringstream ss(query);
        while (!ss.eof()) {
            std::string word;
            ss >> word;
            if (word == "") break;
            words.push_back(word);
        }
        // Print all of the verses
        for (const auto& verse : concord.getVerses(words)) {
            std::cout << verse << std::endl;
        }
        // Loop?
    } while (!isDone());
}