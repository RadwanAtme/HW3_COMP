#ifndef HW3_OUTPUT_CPP_CLASSES_H
#define HW3_OUTPUT_CPP_CLASSES_H
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include "check_funcs.hpp"
#include "hw3_output.hpp"

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

SymTable* symbol_table = new SymTable();
ScopeList* scope_list = new ScopeList();
class Node{
public:
    Node()=default;
};

class TypeNode:public Node{
public:
    string type;
    TypeNode(const string& type):Node(),type(type){}
};

class ConstNode:public Node{
public:
    bool is_const;
    ConstNode(bool var):Node(),is_const(var){}
}

class ExpNode:public Node{
public:
    string id;
    vector<string> types;
    Node(const string& id,const string& type):id(id),types(0){
        types.push_back(type);
    }
    string getType(){
        return types[0];
    }
    void changeType(string type){
        types[0]=type;
    }
};

class FormalsNode:public Node{
public:
    vector<string> id_list;
    vector<string> type_list;
    vector<bool> is_const_list;
    FormalsNode() = default;
    appendIDAndType(string id,string type,bool is_const){
        id_list.push_back(id);
        type_list.push_back(type);
        is_const_list.push_back(is_const);
    }
    appendIDAndType(vector<string> id,vector<string> type,vector<bool> is_const){
        id_list.insert(id_list.end(),id.begin(),id.end());
        type_list.insert(type_list.end(),type.begin(),type.end());
        is_const_list.insert(is_const_list.end(),is_const.begin(),is_const.end());
    }

};
#endif //HW3_OUTPUT_CPP_CLASSES_H
