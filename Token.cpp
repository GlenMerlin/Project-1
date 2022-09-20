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
        case TokenType::LEFTPAREN: return "LEFTPAREN"; break;
        case TokenType::RIGHTPAREN: return "RIGHTPAREN"; break;
        // TODO: add the other types of tokens
        // case TokenType::COLON: return "COLON"; break;
        case TokenType::UNDEFINED: return "UNDEFINED"; break;
        case TokenType::ENDOFFILE: return "ENDOFFILE"; break;
    }
    return "ERROR";
}