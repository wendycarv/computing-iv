// Copyright 2024 Meriem Elkoudi and Wendy Carvalho
#include <SFML/System.hpp>

#include "EDistance.hpp"

int main(int argc, char* argv[]) {
    sf::Clock clock;
    std::string s1, s2;
    std::cin >> s1 >> s2;
    EDistance ed(s1, s2);
    std::cout << "Edit distance = " << ed.optDistance() << std::endl;
    //std::cout << ed.optDistance() << std::endl;
    std::cout << ed.alignment() << std::endl;
    sf::Time t = clock.getElapsedTime();
    std::cout << "\nExecution time is " << t.asSeconds() << " seconds" << std::endl;
}
