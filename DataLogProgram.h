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
    vector<Predicate> body;
    public:
        Predicate setHead(Predicate& predicate) {
            head = predicate;
        }
        vector<Predicate> setBody(Predicate& predicate) {
            body.push_back(predicate);
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