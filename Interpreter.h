#include "DataLogProgram.h"
#include "Database.h"
#include <vector>
using namespace std;

class Interpreter {
    private:
        DataLogProgram DLP;
        Database database;
        vector<Predicate> scheme;
        vector<Predicate> facts;
        vector<Predicate> queries;
    public:
        void run(){
            scheme = DLP.returnSchemes();
            for (unsigned int i = 0; i < facts.size(); i++){
                Header header;
                database.AddRelation(new Relation(scheme[i].returnPredID(), header.createHeaders(scheme[i].returnParams()) ));
            }
            facts = DLP.returnFacts();
            for (unsigned int i = 0; i < facts.size(); i++){
                Tuple tuple;
                Relation* relation = database.GetRelation(facts[i].returnPredID());
                relation->addTuple(tuple.createTuple(facts[i].returnParams()));
            }
            // TODO: Project 4: RULES
            queries = DLP.returnQueries();
            for (unsigned int i = 0; i < queries.size(); i++){
                Relation* relation = database.GetRelation(queries[i].returnPredID());
                // select for each constant in the query ‘q’
                relation->selectInIn();
                // select for each pair of matching variables in ‘q’
                relation->selectInVal();
                // project using the positions of the variables in ‘q’
                relation->project();
                // rename to match the names of variables in ‘q’
                relation->rename();
                //  print the resulting relation
                relation->toString();
            }
        }
    

};