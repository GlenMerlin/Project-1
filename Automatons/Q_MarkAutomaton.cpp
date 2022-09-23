#include "Q_MarkAutomaton.h"

void Q_MarkAutomaton::S0() {
    if (input[index] == '?') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}