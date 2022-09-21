#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton
{
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);

    virtual ~CommentAutomaton() {}
};

#endif // COMMENTAUTOMATON_H

