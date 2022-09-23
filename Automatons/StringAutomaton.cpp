#include "StringAutomaton.h"

void StringAutomaton::S0() {
    if (input[index] == '\''){
        Next();
        S1();
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(){
    if (isalnum(input[index])){
        Next();
        S1();
    }
    else if (input[index] == '\''){
        Next();
        S2();
    }
    else if (index >= input.size()){
        this->type = TokenType::UNDEFINED;
    }
}
void StringAutomaton::S2(){
    if (index >= input.size()){
        return;
    }
    else if (input[index] == '\''){
            inputRead++;
            index++;
            S1();
        }
    else if (input[index] != '\''){
        return;
    }
    else {
        Serr();
    }

}
