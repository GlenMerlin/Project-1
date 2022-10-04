#include "Parser.h"
#include "Lexer.h"

Parser::Parser(std::vector<Token*> tokens) : tokens(tokens), index(0), step(0) {
    index = 0;
    step = 0;

}
Parser::~Parser() {}

void Parser::Match(TokenType type){
    if (type == getTokenType()){
        std::cout << "Matches!" << std::endl;
    }
    else {
        throwErr();
    }
}

TokenType Parser::getTokenType(){
    if (index >= tokens.size()){
        return TokenType::UNDEFINED;
    }
    return tokens.at(index)->getTokenType();
}

void Parser::advanceToken(){
    index++;
}

// TODO: Implement this
const std::string& Parser::prevTokenVal(){

}

void Parser::throwErr(bool problem = false){
    if (index >= tokens.size()) throw tokens.at(tokens.size() - 1);
    // ! figure out how brandon made that a new token
    if (index < 0) throw "Out of Bounds";
    if (problem) throw tokens.at(index);
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
    scheme();
    schemeList();
    Match(TokenType::FACTS);
    Match(TokenType::COLON);
    factList();
    Match(TokenType::RULES);
    Match(TokenType::COLON);
    ruleList();
    Match(TokenType::QUERIES);
    Match(TokenType::COLON);
    query();
    queryList();
    Match(TokenType::ENDOFFILE);
}
// ! Needs to make data structure
void Parser::scheme(){
    Match(TokenType::ID);
    Match(TokenType::LEFTPAREN);
    Match(TokenType::ID);
    idList();
    Match(TokenType::RIGHTPAREN);
}

// ! Needs to make data structure
void Parser::fact(){
    Match(TokenType::ID);
    Match(TokenType::LEFTPAREN);
    Match(TokenType::STRING);
    stringList();
    Match(TokenType::RIGHTPAREN);

}

// ! Needs to make data structure
void Parser::rule(){
    headPredicate();
    Match(TokenType::COLON_DASH);
    predicate();
    predicateList();
    Match(TokenType::PERIOD);

}

// ! Needs to make data structure
void Parser::query(){
    predicate();
    Match(TokenType::Q_MARK);    
}

void Parser::parameter(){

}

void Parser::headPredicate(){
    Match(TokenType::ID);
    Match(TokenType::LEFTPAREN);
    Match(TokenType::ID);
    idList();
    Match(TokenType::RIGHTPAREN);
}

void Parser::predicate(){
    Match(TokenType::ID);
    Match(TokenType::LEFTPAREN);
    parameter();
    parameterList();
    Match(TokenType::RIGHTPAREN);
    
}


void Parser::schemeList(){
    
}

void Parser::factList(){
    
}

void Parser::ruleList(){
    
}

void Parser::queryList(){
    
}

void Parser::predicateList(){

}

void Parser::parameterList(){

}

void Parser::stringList(){

}

void Parser::idList(){

}