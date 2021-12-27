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


struct SymTableCell{
    string name;
    int offset;
    vector<string> type;
    bool is_const;
};

class SymTable{
    unordered_map<string,vector<SymTableCell>> symbol_table;
public:
    void insertToSymTable(string id,string type);
    void deleteFromSymTable(string id);
    bool checkElement(string id);
    bool checkElementType(string id);

};

class ScopeList{
    vector<vector<string>> scopes_list;
    vector<int> scopes_offset;
public:
    void insert(string id);
    void deleteElement(string id);
    void deleteTopScope();
};


class Node{
public:
    string id;
    vector<string> types;
    Node():id(),types(1,"VOID"){}
    Node(const string& id,const string& type):id(id),types(0){
        types.push_back(type);
    }
    string getType(){
        return types[0];
    }
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
