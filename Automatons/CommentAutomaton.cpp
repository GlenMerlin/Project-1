#include "CommentAutomaton.h"

void CommentAutomaton::S0() {
    if(input[index] == '#'){
        Next();
        S1_comment();
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1_comment(){
    if(input[index] == '|'){
        Next();
        S3_block();
    }
    else if (input[index] == '\n'){
        return;
    }
    else if (input[index] != '\n'){
        Next();
        S2_line();
    }
    else {
        Serr();
    }
};
void CommentAutomaton::S2_line(){
    if(EndOfFile() || input[index] == '\n'){
        return;
    }
    else if (input[index] != '\n'){
        Next();
        S2_line();
    }
    else {
        Serr();
    }
    

};
void CommentAutomaton::S3_block(){
    if (EndOfFile()){
        type = TokenType::UNDEFINED;
        return;
    }
    else if (input[index] == '|') {
        Next();
        S4_end();
    }
    else {
        Next();
        S3_block();
    }
};

void CommentAutomaton::S4_end(){
    if (EndOfFile()){
        type = TokenType::UNDEFINED;
        return;
    }
    else if (input[index] == '#'){
        Next();
        return;
    }
    else {
        Next();
        S3_block();
    }
}

