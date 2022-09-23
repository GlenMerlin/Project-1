#ifndef SCHEMEAUTOMATON_H
#define SCHEMEAUTOMATON_H

#include "Automaton.h"

class SchemeAutomaton : public Automaton
{
public:
    SchemeAutomaton() : Automaton(TokenType::SCHEMES) {}  // Call the base constructor

    void S0();
    void S1();
    void S2();
    void S3();
    void S4();
    void S5();
    void S6();

    virtual ~SchemeAutomaton() {}
};

#endif // SCHEMEAUTOMATON_H

