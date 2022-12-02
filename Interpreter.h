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
                cout << "Rule Evaluation" << endl;
                evaluateRules();
                
                cout << "Query Evaluation" << endl;
                queries = DLP.returnQueries();
                for (unsigned int i = 0; i < queries.size(); i++){
                    queries[i].predToString();
                    Relation* relation = evaluatePredicate(queries[i]);
                    relation->toString();
                }
            }


        Relation* evaluatePredicate(Predicate predicate){
            Relation *factRelation = new Relation(database.GetRelation(predicate.returnPredID()));

            vector<Parameter> factParams = predicate.returnParams();
            vector<string> ColumnNames;
            vector<int> ColumnNums;
            map<string, int> variables;

            for (unsigned int j = 0; j < factParams.size(); j++)
            {
                string currParam = factParams[j].parameterToString();
                if (factParams[j].isConstant())
                {
                    factRelation = factRelation->selectInVal(j, currParam);
                }
                else
                {
                    if (variables.find(currParam) == variables.end())
                    {
                        variables.insert({currParam, j});
                        ColumnNames.push_back(currParam);
                        ColumnNums.push_back(j);
                    }
                    else
                    {
                        factRelation = factRelation->selectInIn(variables[currParam], j);
                    }
                }
            }
            factRelation = factRelation->project(ColumnNums);
            factRelation = factRelation->rename(ColumnNames);
            return factRelation;
        }


        void evaluateRules(){
            bool changed = true;
            int loopcount = 0;
            while(changed){
                changed = false;
                loopcount++;
                int sizeBefore = database.size();

                for (auto rule : DLP.returnRules()){
                    rule.ruleToString();
                    cout << '.' << endl;

                    // Step 1: Evaluate Predicates
                    vector<Relation *> finalRelations;
                    for (auto bodyObj : rule.getBody()){
                        finalRelations.push_back(evaluatePredicate(bodyObj));
                    }

                    Relation * relation = finalRelations.at(0);
                    // Step 2: Join
                    if (finalRelations.size() > 1){
                        for (unsigned int i = 1; i < finalRelations.size(); i++){
                            relation = relation->natJoin(finalRelations.at(i));
                        }
                    }

                    // Step 3: Project
                    vector<int> ColumnNums;
                    for (unsigned int i = 0; i < rule.returnHead().returnParams().size(); i++){
                        for (int j = 0; j < relation->returnColumns().headerSize(); j++){
                            if (rule.returnHead().returnParams().at(i).parameterToString() == relation->returnColumns().at(j)){
                                ColumnNums.push_back(j);
                            }
                        }
                    }

                    relation = relation->project(ColumnNums);

                    // Step 4: Rename
                    relation->setHeader(database.GetRelation(rule.getHeadName())->returnColumns());
                    // Step 5: Union
                    database.GetRelation(rule.getHeadName())->unionize(relation);
                }

                int sizeAfter = database.size();
                if (sizeBefore != sizeAfter){
                    changed = true;
                }

            }
            cout << endl << "Schemes populated after " << loopcount << " passes through the Rules." << endl << endl;
        }
        void tupleToString(set<Tuple> tuples, Relation* headRelation, vector<string> ColumnNames){
            for (auto item:tuples){
                cout << "  ";
                for (int i = 0; i < headRelation->returnColumns().headerSize(); i++){
                    cout << (char) tolower(ColumnNames.at(i)[0])  << "=" << item.at(i);
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