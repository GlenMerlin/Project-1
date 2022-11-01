#include <vector>
#include <string>
#include <set>
#include <map>

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
        Relation* selectInVal(int columnIndex, string value);
        Relation* selectInIn(int firstColumn, int secondColumn);
        Relation* project(vector<int> columnsToProject);
        Relation* rename(vector<string> newColumnNames);
        void toString();
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