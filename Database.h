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
};

class Header {
    vector<string> headers;
};

class Relation {
    set<Tuple> tuples;
    void selectInVal();
    void selectInIn();
    void project();
    void rename();
};

class Database {
    map <string, Relation*> databaseMap;
};