#include "SchemeAutomaton.h"

void SchemeAutomaton::S0() {
    if (input[index] == 'S') {
        Next();
        S1();
    }
    else {
        Serr();
    }
}

void SchemeAutomaton::S1(){
    if (input[index] == 'c'){
        Next();
        S2();
    }
    else{
        Serr();
    }
}

void SchemeAutomaton::S2(){
    if (input[index] == 'h'){
        Next();
        S3();
    }
    else{
        Serr();
    }
}
void SchemeAutomaton::S3(){
    if (input[index] == 'e'){
        Next();
        S4();
    }
    else{
        Serr();
    }
}
void SchemeAutomaton::S4(){
    if (input[index] == 'm'){
        Next();
        S5();
    }
    else{
        Serr();
    }
}
void SchemeAutomaton::S5(){
    if (input[index] == 'e'){
        Next();
        S6();
    }
    else{
        Serr();
    }
}

void SchemeAutomaton::S6(){
    if (input[index] == 's'){
        Next();
    }
    else{
        Serr();
    }
}
