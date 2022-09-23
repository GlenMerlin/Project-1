#include "FactsAutomaton.h"

void FactsAutomaton::S0() {
    if (input[index] == 'F') {
        inputRead++;
        index++;
        S1();
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S1(){
    if (input[index] == 'a'){
        inputRead++;
        index++;
        S2();
    }
    else{
        Serr();
    }
}

void FactsAutomaton::S2(){
    if (input[index] == 'c'){
        Next();
        S3();
    }
    else{
        Serr();
    }
}
void FactsAutomaton::S3(){
    if (input[index] == 't'){
        Next();
        S4();
    }
    else{
        Serr();
    }
}
void FactsAutomaton::S4(){
    if (input[index] == 's'){
        Next();
    }
    else{
        Serr();
    }
}