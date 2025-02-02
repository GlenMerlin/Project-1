#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "../Token.h"
#include <iostream>
typedef unsigned int Index;
typedef unsigned int Count;


class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    unsigned int index = 0;
    TokenType type;
    std::string input;

public:
    // Default constructor -- since we have a constructor that takes a parameter,
    //   the compiler will autogenerate a default constructor if not explicit.
    Automaton() : Automaton(TokenType::UNDEFINED) {}

    Automaton(TokenType type) { this->type = type; }

    // Start the automaton and return the number of characters read
    //   read == 0 indicates the input was rejected
    //   read  > 0 indicates the input was accepted
    int Start(const std::string& newInput) {
        input = newInput;
        newLines = 0;
        inputRead = 0;
        index = 0;
        S0();
        return inputRead;
    }

    // Every subclass must define this method
    virtual void S0() = 0;

    void Next(){
        if (input.at(index) == '\n'){
            newLines++;
        }
        inputRead++;
        index++;
    }
    void Match(char check){
        if (input.at(index) == check){
            index++;
        }
        else {
            std::cerr << "Expected: " << check << " Got: " << input.at(index) << "At: " << newLines << std::endl;
            throw;
        }
    }

    bool EndOfFile(){
        return (index >= input.size());
    }

    void Serr() {
        // Indicate the input was rejected
        inputRead = 0;
    }

    virtual Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }

    int NewLinesRead() const { return newLines; }
};

#endif // AUTOMATON_H

