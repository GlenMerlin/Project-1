#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFTPAREN,
    RIGHTPAREN,
    MULTIPLY,
    ADD,
    // TODO: add the other types of tokens
    UNDEFINED,
    ENDOFFILE
};

class Token
{
private:
    TokenType type;
    std::string description;
    int line;

public:
    Token(TokenType type, std::string description, int line);
    void toString();
    std::string enumToString(TokenType);
    // TODO: add other needed methods
};

#endif // TOKEN_H

