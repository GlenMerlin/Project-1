#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if(input[index] == '#'){
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input){
    if(input[index] =='|'){
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
};
void CommentAutomaton::S2(const std::string& input){
    if (input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    }
    else if (isalnum(input[index]) || isspace(input[index])){
        if (input[index] == '\n'){
            // * increase line count
        }
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == EOF){
        // * This needs to become undefined
    }
    else {
        Serr();
    }

};
void CommentAutomaton::S3(const std::string& input){
    if (input[index] == '#'){
        inputRead++;
    }
    else if (input[index] == EOF){
        // * This needs to become undefined
    }
};

