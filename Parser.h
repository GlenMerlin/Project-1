#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Token.h"

class Parser {
private:
    std::vector<Token*> tokens;
public:
    Parser(std::vector<Token*> tokens);
    ~Parser();
    void Match(TokenType type);
    void Run();
    void DataLogProgram();
    void scheme();
    void schemeList();
    void factList();
    void ruleList();
    void query();
    void queryList();

};

#endif //PARSER_H