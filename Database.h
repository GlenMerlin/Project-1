#pragma once
#include <vector>
#include <string>
#include <set>
#include <map>
#include "DataLogProgram.h"

using namespace std;

class Tuple {
    vector<string> values;
    
    public:
        Tuple createTuple(vector<Parameter> parameters){
            for (unsigned int i = 0; i < parameters.size(); i++){
                values.push_back(parameters[i].parameterToString());
            }
            return *this;
        }
        Tuple createTuple(vector<string> parameters){
            for (unsigned int i = 0; i < parameters.size(); i++){
                values.push_back(parameters[i]);
            }
            return *this;
        }
        string at(int index){
            return values.at(index);
        }
        void push_back(string value){
            values.push_back(value);
        }
        bool operator< (const Tuple&rhs) const {
            return values < rhs.values;
        }
        void toString(unsigned int i) {
                cout << values[i];
        }
        int size(){return values.size();};
};

class Header {
    vector<string> headers;
    unsigned int i = 0;
    public:
        Header createHeaders(vector<Parameter> parameters){
            for (unsigned int i = 0; i < parameters.size(); i++){
                headers.push_back(parameters[i].parameterToString());
            }
            return *this;
        }
        Header createHeaders(vector<string> parameters){
            for (unsigned int i = 0; i < parameters.size(); i++){
                headers.push_back(parameters[i]);
            }
            return *this;
        }
        vector<string> returnHeaders(){
            return this->headers;
        }
        string at(int index){
            return headers.at(index);
        }
        void push_back(string value){
            headers.push_back(value);
        }
        void toString(unsigned int i){
            cout << headers.at(i);
        }
        int headerSize(){return headers.size();}
};

class Relation {
    private:
        string name;
        Header columnNames;
        set<Tuple> tuples;
    public:
        Relation() = default;

        Relation(string name, Header columnNames){
            this->name = name;
            this->columnNames = columnNames;
        }

        Relation(string name, Header columnNames, set<Tuple> tuples){
            this->name = name;
            this->columnNames = columnNames;
            this->tuples = tuples;
        }

        Relation(Relation* relation){
            this->name = relation->name;
            this->columnNames = relation->columnNames;
            this->tuples = relation->tuples;
        }
        
        void addTuple(Tuple newTuple) {
            tuples.insert(newTuple);
        }
        
        Relation* selectInVal(int columnIndex, string value){
            Relation* relation = new Relation(name, columnNames);
            for (auto row:tuples){
                if (row.at(columnIndex) == value){
                    relation->addTuple(row);
                }
            }
            return relation;
        }

        Relation* selectInIn(int firstColumn, int secondColumn){
            Relation* relation = new Relation(name, columnNames);
            for (auto row:tuples){
                if (row.at(firstColumn) == row.at(secondColumn)){
                    relation->addTuple(row);
                }
            }
            return relation;
        }

        Relation* project(vector<int> columnsToProject){
            Header newHeader;
            set<Tuple> newTuples;
            for (unsigned int i = 0; i < columnsToProject.size(); i++){
                newHeader.push_back(this->columnNames.at(i));
            }
            for (auto row:tuples){
                Tuple newRow;
                for (auto column:columnsToProject){
                    newRow.push_back(row.at(column));
                }
                newTuples.insert(newRow);
            }
            return new Relation(name, newHeader, newTuples);
        }

        Relation* rename(vector<string> newColumnNames){
            Header newHeader;
            newHeader.createHeaders(newColumnNames);
            return new Relation(name, newHeader, tuples);
        }

        Relation* natJoin(Relation* second){
            map<int, int> matchingIndex;
            Header newHead = joinHeaders(this->columnNames, second->columnNames, matchingIndex);
            set<Tuple> newTuples;
            Tuple newTuple;
            for (auto tuple2:second->tuples){
                for (auto tuple:this->tuples){
                    if (isJoinable(tuple, tuple2, matchingIndex)){
                        newTuple = joinTuples(tuple, tuple2, matchingIndex);
                        newTuples.insert(newTuple);
                    }
                }
            }
            return new Relation(name, newHead, newTuples);
        };

        bool isJoinable(Tuple first, Tuple second, map<int, int> matches){
            for (auto match:matches){
                if (first.at(match.first) == second.at(match.second)){
                    return true;
                }
            }
            return false;
        }

        Header joinHeaders(Header first, Header second, map<int,int> &matches){
            Header newHeader = first;
            vector<string> newParams;
            for (int i = 0; i < second.headerSize(); i++){
                bool match = false;
                for (int j = 0; j < first.headerSize(); j++){
                    if (first.at(j) == second.at(i)){
                        matches.insert({i,j});
                        match = true;
                        newHeader.push_back(second.at(i));
                    }
                }
            }
            return newHeader;    
        }

        Tuple joinTuples(Tuple first, Tuple second, map<int, int> matches){
            vector<string> newParams;
            Tuple newTuple = first;
            bool match = false;
            for (auto match:matches){
                newTuple.push_back(second.at(match.second));
            }
            newTuple.createTuple(newParams);
            return newTuple;
        }

        Header returnColumns(){return columnNames;}
        string getName() {return name;}
        int columnSize(){return columnNames.headerSize();}

        void toString(){
            if (this->tuples.size() > 0){
                cout << "? Yes(" << this->tuples.size() << ")" << endl;
                for (auto tuple:tuples){
                    if (columnNames.headerSize() == 1){
                        cout << "  ";
                        columnNames.toString(0);
                        cout << "=";
                        tuple.toString(0);
                        cout << endl;
                    }
                    else if (columnNames.headerSize() == 0){
                        break;
                    }
                    else {
                        for (int i = 0; i < columnNames.headerSize(); i++){
                            if (i == columnNames.headerSize()-1){
                                columnNames.toString(i);
                                cout << "=";
                                tuple.toString(i);
                            }
                            else if (i == 0){
                                cout << "  ";
                                columnNames.toString(i);
                                cout << "=";
                                tuple.toString(i);
                                cout << ", ";
                            }
                            else {
                                columnNames.toString(i);
                                cout << "=";
                                tuple.toString(i);
                                cout << ", ";
                            }
                        }
                        cout << endl;
                    }
                }
            }
            else {
                cout << "? No" << endl;
            }          
        };
};

class Database {
    private:
        map <string, Relation*> databaseMap;
    public:
        void AddRelation(Relation* newRelation){
            databaseMap.insert({newRelation->getName(), newRelation});
        }
        Relation* GetRelation(string relationName){return databaseMap.at(relationName);}
};