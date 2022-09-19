#include "Lexer.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    std::string filename = argv[1];

    Lexer* lexer = new Lexer();
    
    lexer->Run(filename);

    // TODO

    delete lexer;

    return 0;
}