#include "ColonDashAutomaton.h"

void ColonDashAutomaton::S0() {
    if (input[index] == ':') {
        Next();
        S1();
    }
    else {
        Serr();
    }
}

void ColonDashAutomaton::S1() {
    if (input[index] == '-') {
        inputRead++;
    }
    else {
        Serr();
    }
}