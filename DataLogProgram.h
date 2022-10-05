#include <vector>
#include <string>

using namespace std;

class DataLogProgram {
    private:
    vector<Predicate> scheme;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
};

class Predicate {
    string ID;
    vector <Parameter> parameters;
    public:
        void setName(string name){
            ID = name;
        };
        void addParam(string param){
            Parameter data = Parameter(param);
            parameters.push_back(data);
        };
};

class Rule {
    Predicate head;
    vector<Predicate> Body;
    public:
        Predicate getHead(){
            return head;
        }
        vector<Predicate> getBody(){
            return Body;
        }
};

class Parameter {
    bool isConst;
    string parameter;
    
    public:
        Parameter(string& input){
            parameter = input;
            isConst = (input[0] == '\'');
        };
};