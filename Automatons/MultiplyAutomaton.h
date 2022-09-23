#ifndef MULTIPLYAUTOMATON_H
#define MULTIPLYAUTOMATON_H

#include "Automaton.h"

class MultiplyAutomaton : public Automaton
{
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0();
    virtual ~MultiplyAutomaton() {}
};

#endif // MULTIPLYAUTOMATON_H

