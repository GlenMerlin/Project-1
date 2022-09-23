#include "LeftParenAutomaton.h"

void LeftParenAutomaton::S0() {
    if (input[index] == '(') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}