#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Parameter {
    bool isConst;
    string parameter;
    
    public:
        Parameter(string& input){
            parameter = input;
            isConst = (input[0] == '\'');
        };
        string parameterToString(){
            return parameter;
        };
        bool isConstant(){
            return isConst;
        }
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
        void predToString(){
            std::cout << ID << "(";
            if (parameters.size() > 1) {
                for (unsigned int i = 0; i < parameters.size(); i++){
                    if (i == parameters.size()-1){
                        std::cout << parameters[i].parameterToString();
                    }
                    else {
                        std::cout << parameters[i].parameterToString() << ","; 
                    }
                }
            }
            else{
                std::cout << parameters[0].parameterToString();
            }
            std::cout << ")";
        }
        string returnPredID(){
            return ID;
        }
        vector <Parameter> returnParams(){
            return parameters;
        }
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
        void ruleToString(){
            std::cout << "  ";
            head.predToString();
            std::cout << " :- ";
            for (unsigned int i = 0; i < body.size(); i++){
                body[i].predToString();
                if (i != body.size()-1){
                    std::cout << ",";
                }
            }
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
        void schemeToString(){
            if (scheme.size() > 0){
                for (unsigned int i = 0; i < scheme.size(); i++){
                    std::cout << "  ";
                    scheme[i].predToString();
                    std::cout << std::endl;
                }
            }
            else return;
        }
        void factToString(){
            if (facts.size() > 0){
                for (unsigned int i = 0; i < facts.size(); i++){
                    std::cout << "  ";
                    facts[i].predToString();
                    std::cout << "." << std::endl;
                }
            }
            else return;
        }
        void rulesToString(){
            if (rules.size() > 0){
                for (unsigned int i = 0; i < rules.size(); i++){
                    rules[i].ruleToString();
                    std::cout << '.' << std::endl;
                }
            }
            else return;
        }
        void queryToString(){
            if (queries.size() > 0){
                for (unsigned int i = 0; i < queries.size(); i++){
                    std::cout << "  ";
                    queries[i].predToString();
                    std::cout << "?" << std::endl;
                }
            }
            else return;
        }
        void domainToString(){
            set<string>::iterator it;
            for (it=domain.begin() ; it != domain.end(); it++){
                std::cout << "  " << *it << endl;
            }
        }
        vector<Predicate> returnSchemes(){return scheme;}
        vector<Predicate> returnFacts(){return facts;}
        vector<Predicate> returnQueries(){return queries;}

        int schemeSize(){return scheme.size();};
        int factsSize(){return facts.size();};
        int rulesSize(){return rules.size();};
        int queriesSize(){return queries.size();};
        int domainSize(){return domain.size();};
};