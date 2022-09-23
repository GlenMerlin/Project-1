#ifndef QUERIESAUTOMATON_H
#define QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton
{
public:
    QueriesAutomaton() : Automaton(TokenType::QUERIES) {}  // Call the base constructor

    void S0();
    void S1();
    void S2();
    void S3();
    void S4();
    void S5();
    void S6();


    virtual ~QueriesAutomaton() {}
};

#endif // QUERIESAUTOMATON_H

