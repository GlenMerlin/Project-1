#include "Lexer.h"
#include <iostream>

int main(int argc, char** argv) {

    std::cout << "argc: " << argc << std::endl << "argv: " << argv[1] << std::endl;  
    // TODO: code to read the file in

    Lexer* lexer = new Lexer();

    // TODO

    delete lexer;

    return 0;
}