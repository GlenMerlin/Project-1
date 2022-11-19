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
        vector<Rule> rules;
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
                
                rules = DLP.returnRules();
                // !!! This needs to be changed to true and a base case for the fixed point algorithm
                // !!! needs to be implemented!
                bool tuplesAdded = false;
                do{
                    for (unsigned int i = 0; i < rules.size(); i++){
                        vector<Predicate> body = rules[i].getBody();
                        vector<Relation *> relations;
                        for (unsigned int j = 0; j < body.size(); j++){
                            Relation *relation = database.GetRelation(body[j].returnPredID());
                            Relation *ruleRelation = new Relation(relation);

                            vector<Parameter> ruleParams = body[j].returnParams();
                            vector<string> ColumnNames;
                            vector<int> ColumnNums;
                            map<string, int> variables;

                            for (unsigned int x = 0; x < ruleParams.size(); x++){
                                string currParam = ruleParams[x].parameterToString();
                                if (ruleParams[x].isConstant()){
                                    ruleRelation = ruleRelation->selectInVal(j, currParam);
                                }
                                else{
                                    if (variables.find(currParam) == variables.end()){
                                        variables.insert({currParam, x});
                                        ColumnNames.push_back(currParam);
                                        ColumnNums.push_back(x);
                                    }
                                    else {
                                        ruleRelation = ruleRelation->selectInIn(variables[currParam], j);
                                    }
                                }
                            }
                            ruleRelation = ruleRelation->project(ColumnNums);
                            ruleRelation = ruleRelation->rename(ColumnNames);
                            relations.push_back(ruleRelation);
                        }
                        Relation* finalRelation = relations.at(0);
                        for (unsigned int i = 1; i < relations.size(); i++){
                            finalRelation = finalRelation->natJoin(relations.at(i));
                        }
                        Predicate head = rules[i].returnHead();
                        // what we want
                        vector<Parameter>params = head.returnParams();

                        vector<string>columnNames;
                        vector<int>columnNums;
                        // * getting columnNames
                        for (auto predicate:body){
                            for (auto param: predicate.returnParams()){
                                // look through
                                columnNames.push_back(param.parameterToString());
                            }
                        }
                        // * getting columnNums
                        Header columns = finalRelation->returnColumns();
                        for (auto parameter:params){
                            columnNums.push_back(find(columnNames, parameter));
                        }
                        finalRelation = finalRelation->project(columnNums);
                        finalRelation = finalRelation->rename(columnNames);
                    }
                } while (tuplesAdded);
            
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
        int find(vector<string> columnNames, string toFind){
            for (unsigned int i = 0; i < columnNames.size(); i++){
                if (columnNames.at(i) == toFind){
                    return i;
                }
            }
            throw "syntax error";
        }

};