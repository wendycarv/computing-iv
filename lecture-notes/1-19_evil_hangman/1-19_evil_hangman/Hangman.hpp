//
//  Hangman.hpp
//  1-19_evil_hangman
//
//  Created by wendy on 1/19/24.
//

#ifndef Hangman_hpp
#define Hangman_hpp

#pragma once

#include <stdio.h>
#include <set>
#include <string>
#include <vector>

class Hangman {
public:
    Hangman(const std::vector<std::string>& dictionary, int numGuesses, int wordSize);
    
    bool isOver() const { return isWon() || _guessesLeft <=0; }
    bool isWon() const { return false; }
    int guessesLeft() const {return _guessesLeft;}
    const std::set<char>& guessedLetters() const { return _guessedLetters ;}
    std::string pattern() const;
    
    bool guess(char ch);
private:
    std::vector<std::string> _words;
    std::set<char> _guessedLetters;
    int _guessesLeft;
};

#endif /* Hangman_hpp */
