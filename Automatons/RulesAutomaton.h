#ifndef RULESAUTOMATON_H
#define RULESAUTOMATON_H

#include "Automaton.h"

class RulesAutomaton : public Automaton
{
public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor

    void S0();
    void S1();
    void S2();
    void S3();
    void S4();
    void S5();

    virtual ~RulesAutomaton() {}
};

#endif // RULESAUTOMATON_H

