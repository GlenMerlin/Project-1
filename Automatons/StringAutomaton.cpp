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
    if (input[index] == '\''){
        Next();
        S2();
    }
    else if (EndOfFile()){
        type = TokenType::UNDEFINED;
    }
    else {
        Next();
        S1();
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
