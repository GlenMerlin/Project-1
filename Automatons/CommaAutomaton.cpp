#include "CommaAutomaton.h"

void CommaAutomaton::S0() {
    if (input[index] == ',') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}