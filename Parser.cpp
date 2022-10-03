#include "Parser.h"
#include "Lexer.h"

Parser::Parser(std::vector<Token*> tokens) {
    this->tokens = tokens;
}
Parser::~Parser() {}

void Parser::Match(TokenType type){

}

void Parser::Run(){
    try {
        DataLogProgram();
    }
    catch (std::exception){
        std::cerr << "Oops something went wrong!" << std::endl;
    }
}

void Parser::DataLogProgram(){
    Match(TokenType::SCHEMES);
    Match(TokenType::COLON);
    // TODO: scheme function
    // TODO: schemeList function
    Match(TokenType::FACTS);
    Match(TokenType::COLON);
    // TODO: factList function
    Match(TokenType::RULES);
    Match(TokenType::COLON);
    // TODO: ruleList function
    Match(TokenType::QUERIES);
    Match(TokenType::COLON);
    // TODO: query function
    // TODO: queryList function
    Match(TokenType::ENDOFFILE);
}

void Parser::scheme(){
    
}
void Parser::schemeList(){
    
}
void Parser::factList(){
    
}
void Parser::ruleList(){
    
}
void Parser::query(){
    
}
void Parser::queryList(){
    
}