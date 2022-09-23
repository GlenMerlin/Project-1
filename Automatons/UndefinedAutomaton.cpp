#include "UndefinedAutomaton.h"

void UndefinedAutomaton::S0(){
    if (EndOfFile()){
        Serr();
    }
    else {
        Next();
    }
}