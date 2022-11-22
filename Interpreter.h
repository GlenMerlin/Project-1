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
                    Relation* relation;
                    for (auto rule:rules){
                        rule.ruleToString();
                        cout << '.' << endl;

                        // Step 1: Evaluate Predicates
                        vector<Relation*> finalRelations;
                        for (auto body:rule.getBody()){
                            finalRelations.push_back(evaluatePredicate(body));
                        }

                        relation = finalRelations.at(0);

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
                            for (int j = 0; j < requiredLoops; j++){
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
                    cout << "?????" << endl;
                    tupleToString(relation->returnTuples(), relation);
                } while (tuplesAdded);
                cout << endl << "Schemes populated after " << loopcount << " passes through the Rules." << endl << endl;

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
            map<string, int> seenVals;
            Relation* factRelation = database.GetRelation(predicate.returnPredID());
            vector<int> indexes;
            vector<string> vectorStrings;
            vector<Parameter> parameters = predicate.returnParams();
            for (size_t i = 0; i < parameters.size(); i++){
                string currentParam = predicate.returnParams().at(i);
                if (parameters[i].isConstant()){
                    factRelation = factRelation->selectInVal(i, currentParam);
                }
                else {
                    auto it = seenVals.find(currentParam);
                    size_t secondVal;
                    if (it != seenVals.end()){
                        secondVal = it->second;
                        factRelation = factRelation->selectInIn(secondVal, i);
                    }
                    else {
                        seenVals.insert({currentParam, i});
                        indexes.push_back(i);
                        vectorStrings.push_back(currentParam);
                        factRelation = factRelation->selectInVal(i, currentParam);
                    }
                }
            }
            factRelation = factRelation->project(indexes);
            factRelation = factRelation->rename(vectorStrings);
            return factRelation;
        }
        void tupleToString(set<Tuple> tuples, Relation* headRelation){
            cout << "got here~!" << endl;
            // ! Why No TUPLES
            cout << tuples.size() << endl;
            for (auto item:tuples){
                cout << "  ";
                for (size_t i = 0; i < headRelation->returnColumns().headerSize(); i++){
                    cout << headRelation->returnColumns().returnHeaders().at(i) << "=" << item.at(i);
                    if (i + 1 != headRelation->returnColumns().headerSize()){
                        cout << ", ";
                    }
                }
                cout << endl;
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