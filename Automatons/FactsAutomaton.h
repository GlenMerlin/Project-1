#ifndef FACTSAUTOMATON_H
#define FACTSAUTOMATON_H

#include "Automaton.h"

class FactsAutomaton : public Automaton
{
public:
    FactsAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0();
    void S1();
    void S2();
    void S3();
    void S4();
    void S5();

    virtual ~FactsAutomaton() {}
};

#endif // FACTSAUTOMATON_H

