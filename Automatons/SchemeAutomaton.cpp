#include "SchemeAutomaton.h"

void SchemeAutomaton::S0(const std::string& input) {
    if (input[index] == 'S') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SchemeAutomaton::S1(const std::string& input){
    if (input[index] == 'c'){
        inputRead++;
        index++;
        S2(input);
    }
    else{
        Serr();
    }
}

void SchemeAutomaton::S2(const std::string& input){
    if (input[index] == 'h'){
        inputRead++;
        index++;
        S3(input);
    }
    else{
        Serr();
        }
}
void SchemeAutomaton::S3(const std::string& input){
    if (input[index] == 'e'){
        inputRead++;
        index++;
        S4(input);
    }
    else{
        Serr();
        }
}
void SchemeAutomaton::S4(const std::string& input){
    if (input[index] == 'm'){
        inputRead++;
        index++;
        S5(input);
    }
    else{
        Serr();
        }
}
void SchemeAutomaton::S5(const std::string& input){
    if (input[index] == 'e'){
        inputRead++;
        index++;
    }
    else{
        Serr();
    }
}
