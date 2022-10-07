#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <string>
#include "Token.h"
#include "DataLogProgram.h"
typedef unsigned int Index;

class Parser {
private:
    std::vector<Token*> tokens;
    Index index, step;
    DataLogProgram DLP;
    

public:
    Parser(std::vector<Token*> tokens);
    ~Parser();

// * Helper Functions
    bool Match(TokenType type);
    TokenType getTokenType();
    void advanceToken();
    const std::string prevTokenVal();
    bool listCheck();
    void throwErr(bool problem);
    
// ! might not be needed
    void checkForComments();
    void removeComments();

// * Main functions    
    void Run();
    void DataLogParser();
    void scheme();
    void fact();
    void rule();
    void query();
    void parameter();
    Predicate headPredicate();
    Predicate predicate();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void predicateList(Rule&);
    void parameterList(Predicate&);
    void stringList(Predicate&);
    void idList(Predicate&);
    void toString();

};

#endif //PARSER_H