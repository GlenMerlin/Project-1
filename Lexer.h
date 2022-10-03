#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automatons/Automaton.h"
#include "Token.h"
#include <iostream>

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    std::vector<Token*> getTokens();

};

#endif // LEXER_H

