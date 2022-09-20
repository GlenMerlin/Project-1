#include "Lexer.h"
#include <iostream>
#include <fstream>

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

    // ! This appears to not be reading in multiple lines...
    string input;
    while(getline(inputFile, input));
    Lexer* lexer = new Lexer();
    
    lexer->Run(input);

    delete lexer;

    return 0;
}