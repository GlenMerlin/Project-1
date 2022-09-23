#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton
{
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0();
    void S1_comment();
    void S2_line();
    void S3_block();
    void S4_end();


    virtual ~CommentAutomaton() {}
};

#endif // COMMENTAUTOMATON_H

