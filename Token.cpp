#include "Token.h"
#include "iostream"

Token::Token(TokenType type, std::string description, int line) {
    this->type = type;
    this->description = description;
    this->line = line;
}

void Token::toString(){
    TokenType type = this->type;
    std::string description = this->description;
    int line = this->line;
    std::cout << "(" << enumToString(type) << ",\"" << description << "\"," << line << ")" << std::endl;
}

std::string Token::enumToString(TokenType type){
    switch(type){
        case TokenType::COLON: return "COLON"; break;
        case TokenType::COLON_DASH: return "COLON_DASH"; break;
        case TokenType::COMMA: return "COMMA"; break;
        case TokenType::PERIOD: return "PERIOD"; break;
        case TokenType::Q_MARK: return "Q_MARK"; break;
        case TokenType::LEFTPAREN: return "LEFT_PAREN"; break;
        case TokenType::RIGHTPAREN: return "RIGHT_PAREN"; break;
        case TokenType::MULTIPLY: return "MULTIPLY"; break;
        case TokenType::ADD: return "ADD"; break;
        case TokenType::SCHEMES: return "SCHEMES"; break;
        case TokenType::FACTS: return "FACTS"; break;
        case TokenType::RULES: return "RULES"; break;
        case TokenType::QUERIES: return "QUERIES"; break;
        case TokenType::ID: return "ID"; break;
        case TokenType::STRING: return "STRING"; break;
        case TokenType::COMMENT: return "COMMENT"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
        case TokenType::ENDOFFILE: return "EOF"; break;
    }
    return "ERROR";
}

TokenType Token::getTokenType(){
    return this->type;
}

std::string Token::getDescription(){
    return this->description;
}