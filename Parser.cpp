#include "Parser.h"
#include "Lexer.h"

Parser::Parser() {}
Parser::~Parser() {}

void Parser::Run(std::vector<Token*> tokens){
    for (unsigned int i = 0; i < tokens.size(); i++){
        std::cout << tokens.at(i) << std::endl;
    }
}