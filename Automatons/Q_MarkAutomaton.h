#ifndef Q_MARKAUTOMATON_H
#define Q_MARKAUTOMATON_H

#include "Automaton.h"

class Q_MarkAutomaton : public Automaton
{
public:
    Q_MarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0();
    virtual ~Q_MarkAutomaton() {}
};

#endif // Q_MARKAUTOMATON_H

