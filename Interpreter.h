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
                bool tuplesAdded = true;
                int loopcount = 0;
                do{
                    for (auto rule:rules){
                        rule.ruleToString();
                        cout << '.' << endl;

                        // Step 1: Evaluate Predicates
                        vector<Relation*> finalRelations;
                        for (auto body:rule.getBody()){
                            finalRelations.push_back(evaluatePredicate(body));
                        }

                        Relation* relation = finalRelations.at(0);

                        // Step 2: Projection
                        if (finalRelations.size() > 1){
                            for (unsigned int i = 1; i < finalRelations.size(); i++){
                                relation = relation->natJoin(finalRelations.at(i));
                            }
                        }

                        // Step 3: Project
                        vector<int> ColumnNums;
                        for (unsigned int i = 0; i < rule.returnHead().returnParams().size(); i++){
                            int requiredLoops = relation->returnColumns().headerSize();
                            for (unsigned int j = 0; j < requiredLoops; j++){
                                if (rule.returnHead().returnParams().at(i).parameterToString() == relation->returnColumns().at(j)){
                                    ColumnNums.push_back(j);
                                }
                            }
                        }
                        relation = relation->project(ColumnNums);

                        // Step 4: Rename
                        
                        relation->setHeader(database.GetRelation(rule.returnHead().returnPredID())->getName());

                        // Step 5: Union
                        tuplesAdded = database.GetRelation(rule.getHeadName())->unionize(finalRelations.at(loopcount));
                        loopcount++;
                    }
                    // for (unsigned int i = 0; i < rules.size(); i++){
                    //     vector<Predicate> body = rules[i].getBody();
                    //     Relation* relation;
                    //     vector<Relation *> relations;
                    //     for (unsigned int j = 0; j < body.size(); j++){
                    //         relation = database.GetRelation(body[j].returnPredID());
                    //         Relation *ruleRelation = new Relation(relation);

                    //         vector<Parameter> ruleParams = body[j].returnParams();
                    //         vector<string> ColumnNames;
                    //         vector<int> ColumnNums;
                    //         map<string, int> variables;
                    //         for (unsigned int x = 0; x < ruleParams.size(); x++){
                    //             string currParam = ruleParams[x].parameterToString();
                    //             if (ruleParams[x].isConstant()){
                    //                 ruleRelation = ruleRelation->selectInVal(j, currParam);
                    //             }
                    //             else{
                    //                 if (variables.find(currParam) == variables.end()){
                    //                     variables.insert({currParam, x});
                    //                     ColumnNames.push_back(currParam);
                    //                     ColumnNums.push_back(x);
                    //                 }
                    //                 else {
                    //                     ruleRelation = ruleRelation->selectInIn(variables[currParam], j);
                    //                 }
                    //             }
                    //         }
                    //         ruleRelation = ruleRelation->project(ColumnNums);
                    //         ruleRelation = ruleRelation->rename(ColumnNames);
                    //         relations.push_back(ruleRelation);
                    //     }
                    //     Relation* finalRelation = relations.at(0);
                    //     for (unsigned int i = 1; i < relations.size(); i++){
                    //         finalRelation = finalRelation->natJoin(relations.at(i));
                    //     }
                    //     Predicate head = rules[i].returnHead();
                    //     // what we want
                    //     vector<Parameter>params = head.returnParams();

                    //     vector<string>columnNames;
                    //     vector<int>columnNums;
                    //     // * getting columnNames
                    //     for (auto predicate:body){
                    //         for (auto param: predicate.returnParams()){
                    //             // look through
                    //             columnNames.push_back(param.parameterToString());
                    //         }
                    //     }
                    //     // * getting columnNums
                    //     Header columns = finalRelation->returnColumns();
                    //     int itr = 0;
                    //     for (auto parameter:params){
                    //         for (auto finalParams:finalRelation->returnColumns().returnHeaders()){
                    //             if (finalParams == parameter.parameterToString()){
                    //                 columnNums.push_back(itr);
                    //                 break;
                    //             }
                    //         }
                    //         itr++;
                    //     }
                    //     for (auto column:columnNums){
                    //         cout << "columnNums: " << endl;
                    //         cout << column << endl;
                    //     }

                    //     finalRelation = finalRelation->project(columnNums);
                    //     finalRelation = finalRelation->rename(columnNames);
                    //     tuplesAdded = database.GetRelation(rules[i].getHeadName())->unionize(finalRelation);
                    // }
                    // loopcount++;
                } while (tuplesAdded);
                cout << "Finished with " << loopcount << " loops!" << endl;

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
                }
            }
        Relation* evaluatePredicate(Predicate predicate){
            
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