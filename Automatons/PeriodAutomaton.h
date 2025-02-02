#ifndef PERIODAUTOMATON_H
#define PERIODAUTOMATON_H

#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0();
    virtual ~PeriodAutomaton() {}
};

#endif // PERIODAUTOMATON_H

