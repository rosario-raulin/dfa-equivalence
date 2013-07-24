//
//  DFA.cpp
//  dfa
//
//  Created by Rosario Raulin on 24.07.13.
//  Copyright (c) 2013 Rosario Raulin. All rights reserved.
//

#include "DFA.hpp"

DFA::DFA(const int& start, const int& states, const std::string& alphabet) :
_start(start), _states(states), _alphabet(alphabet) {}

void
DFA::addFinalState(int x) {
    _fstates.insert(x);
}

void
DFA::addTransition(int from, char input, int to) {
    _transitions[std::make_pair(from, input)] = to;
}

bool
DFA::accepts(const std::string &input) const {
    int state = _start;
    
    for (auto it = input.cbegin(); it != input.cend(); ++it) {
        auto trans = _transitions.find(std::make_pair(state, *it));
        if (trans == _transitions.end()) {
            return false;
        } else {
            state = trans->second;
        }
    }
    
    return _fstates.find(state) != _fstates.end();
}

/**
    Helper function that does the actual computation using a table filling
    algorithm.
 **/
void
DFA::fillTable(bool **table) const {
    for (auto it = _fstates.cbegin(); it != _fstates.cend(); ++it) {
        for (int i = 0; i < _states; ++i) {
            if (_fstates.find(i) == _fstates.end()) { // i is not a final state
                table[*it][i] = true;
                table[i][*it] = true;
            }
        }
    }
    
    bool change;
    do {
        change = false;
        
        for (int i = 0; i < _states; ++i) {
            for (int j = 1; j < _states; ++j) {
                if (i != j && !table[i][j]) {
                    for (auto alpha = _alphabet.cbegin();
                         alpha != _alphabet.cend();
                         ++alpha) {
                        auto d1 = _transitions.find(std::make_pair(i, *alpha));
                        auto d2 = _transitions.find(std::make_pair(j, *alpha));
                        
                        int dx = d1->second;
                        int dy = d2->second;
                        
                        if (table[dx][dy] == true) {
                            table[i][j] = true;
                            table[j][i] = true;
                            change = true;
                        }
                    }
                }
            }
        }
    } while (change == true);
}

/**
    Returns a map from a state to all equivalent states.
 **/
std::map<int, std::vector<int>>
DFA::getEquivClasses() const {
    bool** table = new bool*[_states];
    
    for (int i = 0; i < _states; ++i) {
        table[i] = new bool[_states];
        for (int j = 0; j < _states; ++j) {
            table[i][j] = false;
        }
    }
    
    fillTable(table);
    
    std::map<int, std::vector<int>> classes;
    for (int i = 0; i < _states; ++i) {
        bool isMin = true;
        for (int j = 0; j < i; ++j) {
            if (table[i][j] == false) {
                classes[j].push_back(i);
                isMin = false;
            }
        }
        if (isMin) {
            classes[i].push_back(i);
        }
        delete[] table[i];
    }
    
    delete[] table;
    
    return classes;
}