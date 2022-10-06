#include <vector>
#include <set>
#include <string>

using namespace std;

class Parameter {
    bool isConst;
    string parameter;
    
    public:
        Parameter(string& input){
            parameter = input;
            isConst = (input[0] == '\'');
        };
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
        void setHead(Predicate predicate) {
            head = predicate;
        }
        void setBody(Predicate predicate) {
            body.push_back(predicate);
        }
};

class DataLogProgram {
    private:
    vector<Predicate> scheme;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;

    public:
        void addScheme(Predicate& predicate){
            scheme.push_back(predicate);
        }
        void addFact(Predicate& predicate){
            facts.push_back(predicate);
        }
        void addRule(Rule& rule){
            rules.push_back(rule);
        }
        void addQuery(Predicate& predicate){
            queries.push_back(predicate);
        }
        void insertDomain(string input){
            domain.insert(input);
        }
        int schemeSize(){return scheme.size();};
        int factsSize(){return facts.size();};
        int rulesSize(){return rules.size();};
        int queriesSize(){return queries.size();};
        int domainSize(){return domain.size();};
};