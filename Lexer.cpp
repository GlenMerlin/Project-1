#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"


Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());



    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0){
        int maxRead = 0;
        Automaton *maxAutomaton = automata[0];
        while (isspace(input[0])){
            if (input[0] == '\n'){
                lineNumber++;
            } 
            input.erase(0, 1);
        }
        for (unsigned int i = 0; i < automata.size(); i++) {
            int inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
        if (maxRead > 0){
            
            Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            Token *newToken = new Token(TokenType::UNDEFINED, input, lineNumber);
            tokens.push_back(newToken);
        }
        // std::cout << "The string contains: " << input << std::endl;
        input = input.substr(maxRead);
        // std::cout << "The Remaining String contains: " << input  << " maxRead: " << maxRead << std::endl;
    }

    Token *newToken = new Token(TokenType::ENDOFFILE, "", lineNumber);
    tokens.push_back(newToken);
    for (unsigned int i = 0; i < tokens.size(); i++){
        tokens.at(i)->toString();
    }
}

// void Lexer::toString(std::vector<Token*> tokens){
    
// };
