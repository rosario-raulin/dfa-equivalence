//
//  DFA.hpp
//  dfa
//
//  Created by Rosario Raulin on 24.07.13.
//  Copyright (c) 2013 Rosario Raulin. All rights reserved.
//

#ifndef __dfa__DFA__
#define __dfa__DFA__

#include <string>
#include <set>
#include <map>
#include <vector>

class DFA {
private:
    const int _states;
    const std::string _alphabet;
    const int _start;
    std::set<int> _fstates;
    std::map<std::pair<int,char>, int> _transitions;
    
    void fillTable(bool** table) const;
public:
    DFA(const int& start, const int& states, const std::string& alphabet);
    void addFinalState(int x);
    void addTransition(int from, char input, int to);
    bool accepts(const std::string& input) const;
    std::map<int, std::vector<int>> getEquivClasses() const;
};

#endif /* defined(__dea__DAE__) */
