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
        string getName() {return name;}
        void addTuple(Tuple newTuple) {
            tuples.insert(newTuple);
        }
        int columnSize(){return columnNames.headerSize();}

        Relation* selectInVal(int columnIndex, string value){
            Relation* relation = new Relation(name, columnNames);
            for (auto row:tuples){
                if (row.at(columnIndex) == value){
                    relation->addTuple(row);
                }
            }
            return relation;
        };
        Relation* selectInIn(int firstColumn, int secondColumn){
            Relation* relation = new Relation(name, columnNames);
            for (auto row:tuples){
                if (row.at(firstColumn) == row.at(secondColumn)){
                    relation->addTuple(row);
                }
            }
            return relation;
        };
        Relation* project(vector<int> columnsToProject){
            Header newHeader;
            set<Tuple> newTuples;
            for (auto i:columnsToProject){
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
        };
        Relation* rename(vector<string> newColumnNames){
            Header newHeader;
            newHeader.createHeaders(newColumnNames);
            return new Relation(name, newHeader, tuples);
        };
        void toString(){
            if (tuples.size() > 0){
                cout << "? Yes(" << tuples.size() << ")" << endl;
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
        // Project 4 Relational Join
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