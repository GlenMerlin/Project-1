#include "Lexer.h"
#include "Automatons/ColonAutomaton.h"
#include "Automatons/ColonDashAutomaton.h"
#include "Automatons/CommaAutomaton.h"
#include "Automatons/PeriodAutomaton.h"
#include "Automatons/Q_MarkAutomaton.h"
#include "Automatons/LeftParenAutomaton.h"
#include "Automatons/RightParenAutomaton.h"
#include "Automatons/MultiplyAutomaton.h"
#include "Automatons/AddAutomaton.h"
#include "Automatons/SchemeAutomaton.h"
#include "Automatons/FactsAutomaton.h"
#include "Automatons/RulesAutomaton.h"
#include "Automatons/QueriesAutomaton.h"
#include "Automatons/IDAutomaton.h"
#include "Automatons/StringAutomaton.h"
#include "Automatons/CommentAutomaton.h"
#include "Automatons/UndefinedAutomaton.h"


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
    automata.push_back(new SchemeAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new UndefinedAutomaton());
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;
    while (input.size() > 0){
        int maxRead = 0;
        Automaton *maxAutomaton = automata[0];
        while (isspace(input[0]) && !input.empty()){
            if (input[0] == '\n'){
                lineNumber++;
            } 
            input = input.substr(1);
        }
        for (unsigned int i = 0; i < automata.size(); i++) {
            int inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }
        if (!input.empty()){
            Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
            input = input.substr(maxRead);
        }
    }

    Token *newToken = new Token(TokenType::ENDOFFILE, "", lineNumber);
    tokens.push_back(newToken);
    // int tokencount = 0;
    // for (unsigned int i = 0; i < tokens.size(); i++){
    //     tokens.at(i)->toString();
    //     tokencount++;
    // }
    // std::cout << "Total Tokens = " << tokencount;
}
