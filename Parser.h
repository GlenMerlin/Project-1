#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include "Token.h"
typedef unsigned int Index;

class Parser {
private:
    std::vector<Token*> tokens;
    Index index, step;

public:
    Parser(std::vector<Token*> tokens);
    ~Parser();

// * Helper Functions
    bool Match(TokenType type);
    TokenType getTokenType();
    void advanceToken();
    const std::string& prevTokenVal();
    void throwErr(bool problem);
    
// ! might not be needed
    void checkForComments();
    void removeComments();

// * Main functions    
    void Run();
    void DataLogProgram();
    void scheme();
    void fact();
    void rule();
    void query();
    void parameter();
    void headPredicate();
    void predicate();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void predicateList();
    void parameterList();
    void stringList();
    void idList();

};

#endif //PARSER_H