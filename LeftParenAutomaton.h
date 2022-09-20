#ifndef LEFTPARENAUTOMATON_H
#define LEFTPARENAUTOMATON_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton
{
public:
    LeftParenAutomaton() : Automaton(TokenType::LEFTPAREN) {}  // Call the base constructor

    void S0(const std::string& input);
    virtual ~LeftParenAutomaton() {}
};

#endif // LEFTPARENAUTOMATON_H

