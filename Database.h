#include <vector>
#include <string>
#include <set>
#include <map>
#include "DataLogProgram.h"

using namespace std;

class Tuple {
    vector<string> values;
    bool operator< (const Tuple&rhs) const {
        return values < rhs.values;
    }
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
};

class Header {
    vector<string> headers;
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