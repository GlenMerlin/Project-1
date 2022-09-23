#ifndef UNDEFINEDAUTOMATON_H
#define UNDEFINEDAUTOMATON_H

#include "Automaton.h"

class UndefinedAutomaton : public Automaton
{
public:
    UndefinedAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0();

    virtual ~UndefinedAutomaton() {}
};

#endif // UNDEFINEDAUTOMATON_H

