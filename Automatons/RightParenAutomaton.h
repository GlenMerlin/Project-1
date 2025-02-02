#ifndef RIGHTPARENAUTOMATON_H
#define RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton
{
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHTPAREN) {}  // Call the base constructor

    void S0();
    virtual ~RightParenAutomaton() {}
};

#endif // RIGHTPARENAUTOMATON_H

