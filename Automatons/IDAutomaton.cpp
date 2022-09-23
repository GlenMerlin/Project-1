#include "IDAutomaton.h"

void IDAutomaton::S0() {
    if (isalpha(input[index])) {
        Next();
        S1();
    }
    else {
        Serr();
    }
}
void IDAutomaton::S1() {
        if (isalnum(input[index])){
            Next();
            S1();
        }
}