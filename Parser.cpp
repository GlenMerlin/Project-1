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
        throwErr(true);
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

const std::string& Parser::prevTokenVal(){
    // * This is an out of bounds check
    throwErr(false);
    return tokens.at(index-1)->getDescription();
}
void Parser::throwErr(bool problem = false){
    if (index >= tokens.size()) throw tokens.at(tokens.size() - 1);
    if (index < 0) throw Token(TokenType::UNDEFINED, "Out Of Bounds", 0);
    if (problem) throw tokens.at(index);
}

void Parser::Run(){
    try {
        DataLogParser();
        std::cout << "Success!" << std::endl;
    }
    catch (std::exception){
        std::cerr << "Failure!" << std::endl;
    }
}

void Parser::DataLogParser(){
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

void Parser::scheme(){
    Match(TokenType::ID);
    Predicate scheme;
    scheme.setName(prevTokenVal());
    Match(TokenType::LEFTPAREN);
    Match(TokenType::ID);
    scheme.addParam(prevTokenVal());
    idList(scheme);
    Match(TokenType::RIGHTPAREN);
    DLP.addScheme(scheme);
    
}

void Parser::fact(){
    Match(TokenType::ID);
    Predicate fact;
    fact.setName(prevTokenVal());
    Match(TokenType::LEFTPAREN);
    Match(TokenType::STRING);
    fact.addParam(prevTokenVal());
    DLP.insertDomain(prevTokenVal());
    stringList(fact);
    Match(TokenType::RIGHTPAREN);
}

void Parser::rule(){
    Rule rule;
    rule.setHead(headPredicate());
    Match(TokenType::COLON_DASH);
    rule.setBody(predicate());
    predicateList(rule);
    Match(TokenType::PERIOD);
    DLP.addRule(rule);
}

void Parser::query(){
    Predicate query;
    query = predicate();
    Match(TokenType::Q_MARK);
    DLP.addQuery(query);    
}

void Parser::parameter(){
    if (!Match(TokenType::STRING) && !Match(TokenType::ID)) throwErr(true);
    // TODO: this needs to return the parameter object made out of that token
    return;
}

Predicate Parser::headPredicate(){
    Predicate predicate;
    Match(TokenType::ID);
    Match(TokenType::LEFTPAREN);
    Match(TokenType::ID);
    idList(predicate);
    Match(TokenType::RIGHTPAREN);
    return predicate;
}

Predicate Parser::predicate(){
    Predicate predicate;
    Match(TokenType::ID);
    predicate.setName(prevTokenVal());
    Match(TokenType::LEFTPAREN);
    parameter();
    predicate.addParam(prevTokenVal());
    parameterList();
    Match(TokenType::RIGHTPAREN);
    return predicate;
}

void Parser::schemeList(){
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        scheme();
        schemeList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::FACTS) return;
    else throwErr();
}

void Parser::factList(){
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        fact();
        factList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::RULES) return;
    else throwErr();
}

void Parser::ruleList(){
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        rule();
        ruleList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::QUERIES) return;
    else throwErr();
}

void Parser::queryList(){
    if (tokens.at(index)->getTokenType() == TokenType::ID){
        query();
        queryList();
    }
    else if (tokens.at(index)->getTokenType() == TokenType::ENDOFFILE) return;
    else throwErr();
}

void Parser::predicateList(Rule& rule){
    if(!Match(TokenType::COMMA)) return;
    rule.setBody(predicate());
    predicateList(rule);
}

void Parser::parameterList(){
    if(!Match(TokenType::COMMA)) return;
    parameter();
    parameterList();
}

void Parser::stringList(Predicate& predicate){
    if(!Match(TokenType::COMMA)) return;
    Match(TokenType::STRING);
    predicate.addParam(prevTokenVal());
    DLP.insertDomain(prevTokenVal());
    stringList(predicate);
}

void Parser::idList(Predicate& predicate){
    if(!Match(TokenType::COMMA)) return;
    Match(TokenType::ID);
    predicate.addParam(prevTokenVal());
    idList(predicate);
}

void Parser::toString(){
    std::cout << "Schemes("<< DLP.schemeSize() <<"): " << std::endl;
    // for (unsigned int i = 0; i < DLP.schemeSize(); i++){
    //     std::cout << "  " << schemes[i] << std::endl;
    // }
    std::cout << "Facts("<< DLP.factsSize() <<"): " << std::endl;
    // for (unsigned int i = 0; i < facts.size(); i++){
    //     std::cout << "  " << facts[i] << std::endl;
    // }
    std::cout << "Rules("<< DLP.rulesSize() <<"): " << std::endl;
    // for (unsigned int i = 0; i < rules.size(); i++){
    //     std::cout << "  " << rules[i] << std::endl;
    // }
    std::cout << "Queries("<< DLP.queriesSize() <<"): " << std::endl;
    // for (unsigned int i = 0; i < queries.size(); i++){
    //     std::cout << "  " << queries[i] << std::endl;
    // }
    std::cout << "Domain("<< DLP.domainSize() <<"): "<< std::endl;
    // for (unsigned int i = 0; i < domain.size(); i++){
    //     std::cout << "  " << domain[i] << std::endl;
    // }
}