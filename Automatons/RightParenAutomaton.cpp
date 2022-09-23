#include "RightParenAutomaton.h"

void RightParenAutomaton::S0() {
    if (input[index] == ')') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}