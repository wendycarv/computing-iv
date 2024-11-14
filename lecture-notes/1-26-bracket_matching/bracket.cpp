#include "bracket.hpp"
#include <stack>

bool isLBracket(char c) {
    return std::string("<[{(".find(c) != std::string::npos);
}

bool isRBracket(char c) {
    return std::string("<)}]".find(c) != std::string::npos);
}

bool areMatch(char l, char r) {

}

bool isMatched(const std::string& line) {

    // if string is empty

    if (line.size() == 0) {
        return true;
    }

    std::stack<char> test;

    for (char c : line) {
        if (isLBracket(c)) {
            test.push(c);
        } else if (isRBracket(c)) {
            if (!test.empty() && areMatch(test.top(), c) {
                test.pop();
            } else {
                return false;
            }
        }
    }
    return test.empty;
}