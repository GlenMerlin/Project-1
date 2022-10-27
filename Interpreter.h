#include "DataLogProgram.h"
using namespace std;

class Interpreter {
    private:
        DataLogProgram DLP;
    public:
        void run(){
            for (unsigned int i = 0; i < DLP.schemeSize(); i++){
                // TODO: create a relation using name and parameter values from ‘s’
            }
            for (unsigned int i = 0; i < DLP.factsSize(); i++){
                // make a tuple ‘t’ using the values from ‘f’
                // add ‘t’ to relation with the same name as ‘f’
            }
            for (unsigned int i = 0; i < DLP.queriesSize(); i++){
/*
                get the relation ‘r’ with the same name as the query ‘q’
                select for each constant in the query ‘q’
                select for each pair of matching variables in ‘q’
                project using the positions of the variables in ‘q’
                rename to match the names of variables in ‘q’
                print the resulting relation
*/
            }
        }
    

};