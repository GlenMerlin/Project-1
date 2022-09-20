#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    int maxRead = 0;
    while (input.size() > 0){
        Automaton *maxAutomaton = automata[0];
        for (unsigned int i = 0; i < automata.size(); i++) {
            int inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
        if (maxRead > 0){
            Token *newToken = maxAutomaton->CreateToken(input.substr(maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            Token *newToken = new Token(TokenType::UNDEFINED, input, lineNumber);
            tokens.push_back(newToken);
        }
        input = input.substr(maxRead);
        std::cout << "The Remaining String contains: " << input << std::endl;
    }

    Token *newToken = new Token(TokenType::ENDOFFILE, "", lineNumber);
    tokens.push_back(newToken);
    for (unsigned int i = 0; i < tokens.size(); i++){
        tokens.at(i)->toString();
    }
}

// void Lexer::toString(std::vector<Token*> tokens){
    
// };
