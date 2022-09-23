#include "RulesAutomaton.h"

void RulesAutomaton::S0() {
    if (input[index] == 'R') {
        Next();
        S1();
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S1(){
    if (input[index] == 'u'){
        Next();
        S2();
    }
    else{
        Serr();
    }
}

void RulesAutomaton::S2(){
    if (input[index] == 'l'){
        Next();
        S3();
    }
    else{
        Serr();
    }
}
void RulesAutomaton::S3(){
    if (input[index] == 'e'){
        Next();
        S4();
    }
    else{
        Serr();
    }
}
void RulesAutomaton::S4(){
    if (input[index] == 's'){
        Next();
    }
    else{
        Serr();
    }
}