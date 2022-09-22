#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input){
    if (isalnum(input[index])){
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] == '\''){
        inputRead++;
        index++;
        S2(input);
    }
}
void StringAutomaton::S2(const std::string& input){
    if (inputRead != input.size()){
        if (input[index] == '\''){
            S1(input);
            // * This becomes a ' ? 
        }
        else if (isalnum(input[index])){
            // * This becomes undefined?
        }
        else {
            Serr();
        }
    }

}
