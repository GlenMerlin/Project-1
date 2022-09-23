#include "QueriesAutomaton.h"

void QueriesAutomaton::S0() {
    if (input[index] == 'Q') {
        Next();
        S1();
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S1(){
    if (input[index] == 'u'){
        Next();
        S2();
    }
    else{
        Serr();
    }
}

void QueriesAutomaton::S2(){
    if (input[index] == 'e'){
        Next();
        S3();
    }
    else{
        Serr();
    }
}
void QueriesAutomaton::S3(){
    if (input[index] == 'r'){
        Next();
        S4();
    }
    else{
        Serr();
    }
}
void QueriesAutomaton::S4(){
    if (input[index] == 'i'){
        Next();
        S5();
    }
    else{
        Serr();
    }
}

void QueriesAutomaton::S5(){
    if (input[index] == 'e'){
        Next();
        S6();
    }
    else{
        Serr();
    }
}

void QueriesAutomaton::S6(){
    if (input[index] == 's'){
        Next();
    }
    else{
        Serr();
    }
}
