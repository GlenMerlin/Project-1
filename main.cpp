#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
int main(int argc, char** argv) {
    if (argc < 1) {
        cerr << "No Input file provided" << endl << "Usage: ./main input.txt" << endl;
        return 1;
    }
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Couldn't open " << argv[1] << " for input " << endl;
        return 1;
    };

    string input;
    stringstream ss;

    ss << inputFile.rdbuf();
    
    input = ss.str();
    Lexer* lexer = new Lexer();
    
    lexer->Run(input);
    vector<Token*> tokens = lexer->getTokens();
 
    Parser* parser = new Parser(tokens);
    parser->Run();
    
    Interpreter* interpreter =  new Interpreter(parser->getDataLog());
    interpreter->Run();

    delete parser;
    delete lexer;
    delete interpreter;

    return 0;
}