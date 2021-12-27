#ifndef HW3_OUTPUT_CPP_CLASSES_H
#define HW3_OUTPUT_CPP_CLASSES_H
#include <vector>
#include <string>
#include <unordered_map>
#include <list>


extern int yylineno;

#define YYSTYPE Node*

using std::string;
using std::vector;
using std::unordered_map;
using std::list;

enum Types{
    INT,
    BYTE,
    BOOL,
    STRING,
};

struct NTO {
    Types type;
    string name;
    int offest ;
    bool is_const;
};

class SymTable{
    list<vector<NTO>> Stacktable;
    vector<int> offests;

public:
    void insertToSymTable(string id,Types type);
    void deleteFromSymTable(string id);
    bool checkElement(string id);
    bool checkElementType(string id);

    CheckMain
    checkDoubleDecleration
    insertFunc(type1,type2,type)
    getElementType  (/**the type of the last element*/)
    getFunRetVal

    void openScope(){
        Stacktable.push_back(new vector<NTO>);
        vector.push_back(vector.back());
    }
};

struct Scope {
    vector<string> v ;
    bool Iswhile;
};

class ScopeList{
    vector<Scope> scopes_list;
    vector<int> scopes_offset;

public:
    void insert(string id);
    void deleteElement(string id);
    void deleteTopScope();

    void openWhileScope();
    void openWhileScope();
    void closeScope(); /**  */
    checkdoubledecleration /** */
    checkIFWhileScope




};

class Node{
    string id;
    Types type;
};


class Num:public Node{
public:
    int value;
    Num(const string& id,const string& type,int value):Node(id,type),value(value){}
};

class Boolean:public Node{
public:
    bool value;
    Boolean(const string& id,const string& type,bool value):Node(id,type),value(value){}
};

#endif //HW3_OUTPUT_CPP_CLASSES_H
