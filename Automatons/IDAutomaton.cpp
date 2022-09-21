#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    // ? Does this need to handle alternating caps?
    if(input == "Schemes") {
        inputRead = 7;
        Serr();
    }
    else if(input == "Facts") {
        inputRead = 5;
        Serr();
    }
    else if(input == "Rules") {
        inputRead = 5;
        Serr();
    }
    else if(input == "Queries") {
        inputRead = 7;
        Serr();
    }
    else if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
// ! This has touble handling not grabbing the following characters...
void IDAutomaton::S1(const std::string& input) {
    for (unsigned int i = 1; i < input.length(); i++){
        if (isalpha(input[index]) || isdigit(input[index])){
            inputRead++;
            index++;
        }
        else {
            i = input.length();
        }
    }
}