#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Token.h"

class Parser {
private:
    
public:
    Parser();
    ~Parser();

    void Run(std::vector<Token*> tokens);

};

#endif //PARSER_H