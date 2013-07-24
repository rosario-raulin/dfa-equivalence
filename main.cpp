//
//  main.cpp
//  dea
//
//  Created by Rosario Raulin on 24.07.13.
//  Copyright (c) 2013 Rosario Raulin. All rights reserved.
//

#include "DAE.hpp"

#include <iostream>

int main(int argc, const char * argv[])
{
    DAE dae(0, 6, "ab");
    
    dae.addFinalState(0);
    dae.addFinalState(2);
    
    dae.addTransition(0, 'a', 1);
    dae.addTransition(0, 'b', 3);
    dae.addTransition(1, 'a', 4);
    dae.addTransition(1, 'b', 2);
    dae.addTransition(2, 'a', 1);
    dae.addTransition(2, 'b', 5);
    dae.addTransition(3, 'a', 0);
    dae.addTransition(3, 'b', 4);
    dae.addTransition(4, 'a', 4);
    dae.addTransition(4, 'b', 4);
    dae.addTransition(5, 'a', 2);
    dae.addTransition(5, 'b', 4);
    
    std::map<int, std::vector<int>> equivClasses = dae.getEquivClasses();

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

