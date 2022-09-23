#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton
{
public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0();
    void S1();
    void S2();

    virtual ~StringAutomaton() {}
};

#endif // STRINGAUTOMATON_H

