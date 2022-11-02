#include "DataLogProgram.h"
#include "Database.h"
#include <vector>
#include <iostream>
using namespace std;

class Interpreter {
    private:
        DataLogProgram DLP;
        Database database;
        vector<Predicate> schemes;
        vector<Predicate> facts;
        vector<Predicate> queries;
    public:
        Interpreter(DataLogProgram DLP){
            this->DLP = DLP;
        };
        void Run(){
            schemes = DLP.returnSchemes();
            for (unsigned int i = 0; i < schemes.size(); i++){
                Header header;
                database.AddRelation(new Relation(schemes[i].returnPredID(), header.createHeaders(schemes[i].returnParams()) ));
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
                queries[i].predToString();
                Relation* relation = database.GetRelation(queries[i].returnPredID());
                Relation* queryRelation = new Relation(relation);

                vector<Parameter> queryParams = queries[i].returnParams();
                vector<string> ColumnNames;
                vector<int> ColumnNums;
                map<string, int> variables;

                for (unsigned int j = 0; j < queryParams.size(); j++){
                    string currParam = queryParams[j].parameterToString();
                    if (queryParams[j].isConstant()){
                        queryRelation = queryRelation->selectInVal(j, currParam);
                    }
                    else {
                        if (variables.find(currParam) == variables.end()){
                            variables.insert({currParam, j});
                            ColumnNames.push_back(currParam);
                            ColumnNums.push_back(j);
                        }
                        else {
                            queryRelation = queryRelation->selectInIn(variables[currParam], j);
                        }
                    }
                }
                queryRelation = queryRelation->project(ColumnNums);
                queryRelation = queryRelation->rename(ColumnNames);
                //  print the resulting queryRelation
                queryRelation->toString();
                delete queryRelation;
            }
        }
    

};