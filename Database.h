#pragma once
#include <vector>
#include <string>
#include <set>
#include <map>
#include "DataLogProgram.h"

using namespace std;

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
        string toStr(Header header){
            if (size() != header.headerSize()){
                throw;
            }
            stringstream out;
            string sep = "";
            for (int i = 0; i < size(); i++){
                string name = header.at(i);
                string value = at(i);
                out << sep << name << "=" << value;
                sep = ", ";
            }
            return out.str();
        }
        int size(){return values.size();};
};



class Relation {
    private:
        string name;
        Header columnNames;
        set<Tuple> tuples;
        map<int, int> matches;
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
            for (auto i : columnsToProject){
                newHeader.push_back(this->columnNames.at(i));
            }
            for (auto row:tuples){
                Tuple newRow;
                for (auto i : columnsToProject){
                    newRow.push_back(row.at(i));
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
            Relation* r1 = this;
            Relation* r2 = second;
            // might not be needed
            string newName = (r1->getName() + " |x| " + r2->getName());

            Header h1 = r1->returnColumns();
            Header h2 = r2->returnColumns();

            vector<int> uniqueCols;

            for (int i = 0; i < h2.headerSize(); i++){
                bool found = false;

                for (int j = 0; j < h1.headerSize(); j++){
                    if (h1.at(j) == h2.at(i)){
                        found = true;
                        matches.insert({j,i});
                    }
                }
                if (!found){
                    uniqueCols.push_back(i);
                }
            }

            Header newHead = joinHeaders(h1, h2);


            set<Tuple> newTuples;
            for (auto t1 : r1->returnTuples()){
                for (auto t2: r2->returnTuples()){
                    if (isJoinable(t1, t2)){
                        Tuple newTuple = joinTuples(t1, t2, uniqueCols);
                        newTuples.insert(newTuple);
                    }
                }
            }
            return new Relation(newName, newHead, newTuples);
        };

        bool isJoinable(Tuple first, Tuple second){
            for (auto [i, j] : matches){
                if (first.at(i) != second.at(j)){
                    return false;
                }
            }
            return true;
        }

        Header joinHeaders(Header first, Header second){
            Header newHeader = first;
            for (int i = 0; i < second.headerSize(); i++){
                bool unique = true;
                for (int j = 0; j < first.headerSize(); j++){
                    if (first.at(j) == second.at(i)){
                        unique = false;
                        matches.insert({j,i});
                    }
                }
                if (unique){
                    newHeader.push_back(second.at(i));
                }
            }
            return newHeader;    
        }

        Tuple joinTuples(Tuple first, Tuple second, vector<int>& uniqueCols){

            Tuple newTuple = first;

            for (auto i : uniqueCols){
                newTuple.push_back(second.at(i));
            }

            return newTuple;
        }

        void unionize(Relation* finalRelation){
            for (auto item:finalRelation->returnTuples()){
                if (tuples.insert(item).second){
                    cout << "  " << item.toStr(finalRelation->returnColumns()) << endl;
                }
            }
        }

        void setHeader(const Header &header){
            columnNames = header;
        }

        Header returnColumns(){return columnNames;}
        set<Tuple> returnTuples(){return tuples;}
        string getName() {return name;}
        int columnSize(){return columnNames.headerSize();}
        int tupleSize(){return tuples.size();}

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
        int size(){
            int size = 0;
            for (auto i : databaseMap){
                size += i.second->tupleSize();
            }
            return size;
        }
};