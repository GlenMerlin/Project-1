#include "AddAutomaton.h"

void AddAutomaton::S0() {
    if (input[index] == '+') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}