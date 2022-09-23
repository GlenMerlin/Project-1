#include "MultiplyAutomaton.h"

void MultiplyAutomaton::S0() {
    if (input[index] == '*') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}