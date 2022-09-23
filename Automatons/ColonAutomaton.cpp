#include "ColonAutomaton.h"

void ColonAutomaton::S0() {
    if (input[index] == ':') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}