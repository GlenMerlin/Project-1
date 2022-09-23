#include "PeriodAutomaton.h"

void PeriodAutomaton::S0() {
    if (input[index] == '.') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}