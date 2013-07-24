//
//  main.cpp
//  dea
//
//  Created by Rosario Raulin on 24.07.13.
//  Copyright (c) 2013 Rosario Raulin. All rights reserved.
//

#include "DFA.hpp"

#include <iostream>

int main(int argc, const char * argv[])
{
    DFA d(0, 6, "ab");
    
    d.addFinalState(0);
    d.addFinalState(2);
    
    d.addTransition(0, 'a', 1);
    d.addTransition(0, 'b', 3);
    d.addTransition(1, 'a', 4);
    d.addTransition(1, 'b', 2);
    d.addTransition(2, 'a', 1);
    d.addTransition(2, 'b', 5);
    d.addTransition(3, 'a', 0);
    d.addTransition(3, 'b', 4);
    d.addTransition(4, 'a', 4);
    d.addTransition(4, 'b', 4);
    d.addTransition(5, 'a', 2);
    d.addTransition(5, 'b', 4);
    
    std::map<int, std::vector<int>> equivClasses = d.getEquivClasses();

    for (auto it = equivClasses.cbegin(); it != equivClasses.cend(); ++it) {
        std::cout << "[";
        
        auto inner = it->second.cbegin();
        while ((inner+1) != it->second.cend()) {
            std::cout << *inner << ", ";
            ++inner;
        }
        std::cout << *inner << "]" << std::endl;
    }
    
    return 0;
}

