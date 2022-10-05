#include "Parser.h"
#include "Lexer.h"

Parser::Parser(std::vector<Token*> tokens) : tokens(tokens), index(0), step(0) {
    index = 0;
    step = 0;

}
Parser::~Parser() {}

bool Parser::Match(TokenType type){
    if (type == getTokenType()){
        std::cout << "Matches!" << std::endl;
        advanceToken();
        return true;
    }
    else {
        throwErr();
        return false;
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

void Parser::throwErr(){
    if (index >= tokens.size()) throw tokens.at(tokens.size() - 1);
    // ! figure out how brandon made that a new token
    if (index < 0) throw "Out of Bounds";
    // ! if (problem) throw tokens.at(index);
}

void Parser::Run(){
    try {
        DataLogProgram();
        std::cout << "Success!" << std::endl;
    }
    catch (std::exception){
        std::cerr << "Failure!" << std::endl;
    }
}

void Parser::DataLogProgram(){
    std::cout << "Inside DataLog " << std::endl;
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
    if (!Match(TokenType::STRING) && !Match(TokenType::ID)) throwErr();
    // TODO: this needs to return the parameter object made out of that token
    return;
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

// ! the following all infinite loop :(
void Parser::schemeList(){
    std::cout << "Inside schemeList" << std::endl;
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        scheme();
        schemeList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::FACTS){
        return;
    }

    schemeList();
}

void Parser::factList(){
    std::cout << "Inside factList" << std::endl;
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        fact();
        factList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::RULES){
        return;
    }
    else {
        throwErr();
    }
}

void Parser::ruleList(){
    std::cout << "Inside ruleList" << std::endl;
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        rule();
        ruleList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::QUERIES){
        return;
    }
    else {
        throwErr();
    }
}

void Parser::queryList(){
    std::cout << "Inside queryList" << std::endl;
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        query();
        queryList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::ENDOFFILE){
        return;
    }
    else {
        throwErr();
    }
}

void Parser::predicateList(){
    std::cout << "Inside predicateList" << std::endl;
    if(!Match(TokenType::COMMA)) return;
    predicate();
    predicateList();
}

void Parser::parameterList(){
    std::cout << "Inside parameterList" << std::endl;
    if(!Match(TokenType::COMMA)) return;
    parameter();
    parameterList();
}

void Parser::stringList(){
    std::cout << "Inside stringList" << std::endl;
    if(!Match(TokenType::COMMA)) return;
    Match(TokenType::STRING);
    stringList();
}

void Parser::idList(){
    std::cout << "Inside idList" << std::endl;
    if(!Match(TokenType::COMMA)) return;
    Match(TokenType::ID);
    idList();
}