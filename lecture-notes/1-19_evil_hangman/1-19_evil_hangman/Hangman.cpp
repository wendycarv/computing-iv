//
//  Hangman.cpp


#include <stdio.h>
#include "Hangman.hpp"

Hangman::Hangman(const std::vector<std::string>& dictionary, int numGuesses, int wordSize): _guessesLeft(numGuesses){
    
    std::copy_if(dictionary.begin(),dictionary.end(),std::back_inserter(<#Container &x#>)){
        [=](auto word) { return word.size() == wordSize; } //anonymous function, use here and throw away //auto word is the function's parameter
    }
}

std::string Hangman::pattern() const {
    return mask(_words.front());
}

bool Hangman::guess(char ch) {
    _guessedLetters.insert(ch);
    std::unordered_map<std::string, std::vector<std::string>> groups;
    
    // separate words into groups
    for (auto & w:_words) {
        groups[mask(w)].push_back(w);
    }
    // pick a group
    auto newPattern = std::max_element(groups.begin(), groups.end())
    [](auto p1, auto p2) {return p1.second.size() < p2.second}
    _words = groups[newPattern];
    // check if guess was correct
    bool isCorrect = newPattern.find(ch) != std::string::npos;

    _guessesLeft-= !isCorrect;
    return isCorrect;
}

std::string Hangman::mask(const std::string word) const {
    std::string result;
    std::transform(word.begin(),word.end(), std::back_inserter());
    
    return result;
}
