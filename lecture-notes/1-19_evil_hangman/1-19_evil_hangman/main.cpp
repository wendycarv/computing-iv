#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Hangman"

int main(int argc, const char * argv[]) {
    
    //set up game
    int wordSize = 7;
    Hangman game(dictionary, numGuesses, wordSize);
    
    //check if the game is over
    while (!game.isOver()) {
        //display the game state
        std::cout << game.pattern() << std::endl;
        //display word pattern
        //display the guesses letters
        //display how many guesses remain
        for (char c : game.guessedLetters) {
            std::cout << c << ", ";
        }
        std::cout << std::endl;
        std::cout << "Guesses remaining: " << game.guessesLeft() << std::endl;
        
        //ask the user for a letter
        std::cout<< "Guess a letter: " << std::flush;
        char ch;
        std::cin >> ch;
        //update the game state
        if (game.guess(ch)) {
            std::cout << ch << " was in the weord" << std::endl;
        } else {
            std::cout << ch << " was not in the weord" << std::endl;
        }
        
    }
    
    if (game.isWon()){
        std::cout << "Congratulations!" << std::endl;
    } else {
        std::cout << "Better luck next time." << std::endl;
    }
    
    std::cout << "The word was " << game.word() << std::endl;
    return 0;
}
