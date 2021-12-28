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
using std::list;

struct SymTableCell {
    string id;
    string type;
    int offset;
    bool is_const;
    vector<string> arg_types;
    SymTableCell(string id, string ret_type, vector<string> arg_types):id(id),type(ret_type),offset(0),
                        is_const(false),arg_types(arg_types){
    }
    SymTableCell(const SymTableCell& cell):id(cell.id),type(cell.type),offset(cell.offset),
                    is_const(cell.is_const),arg_types(cell.arg_types){

    }
    SymTableCell(string id,string type,bool is_const):id(id),type(type),offset(0),
                        is_const(is_const){

    }
    ~SymTableCell() = default;
};




class SymTable{
    unordered_map<string,SymTableCell> table;

public:
    void insertToSymTable(string id,string type,bool is_const); // ok

    void checkMain(); // ok
    void checkDoubleDecleration(string id,int yylineno); // ok
    void insertFunc(string id,string ret_type,vector<string> arg_types); //ok
    void checkNotConst(string id,int yylineno); //ok
    void checkElementExists(string id,int yylineno); // ok
    string getElementType(string id); //ok
    void checkFunction(string id,vector<string> types,int yylineno);//ok
    ~SymTable()=default;
    SymTable(){

    }
};


class Scope {
public:
    vector<SymTableCell> v ;
    bool Iswhile;
    Scope(bool is_while = 0): v(vector<SymTableCell>()){
        Iswhile = is_while;
    }
};


class ScopeList{
    vector<Scope> scopes_list;
    vector<int> scopes_offset;
    bool is_while;

public:

    void openScope(){
        scopes_offset.push_back(scopes_offset.back());
        scopes_list.push_back(Scope());
    }
    void closeScope(){
        scopes_offset.pop();
        scopes_list.pop();

    }
    void openWhileScope(){
        scopes_offset.push_back(scopes_offset.back());
        scopes_list.push_back(Scope(1));
        is_while = 1;

    }
    bool checkIfWhileScope(){
        return is_while;

    }

    void openFuncScope(string RetType,vector<string> id_list,vector<string> types){
        SymTableCell s;
        s.type = RetType;
        s.name ="func ";
        s.is_const = 0;
        s.offest = 0;
        scopes_list.back().v.push_back(s);
        scopes_list.puch_back(Scope());


        scopes_offset.push_back(scopes_offset.back());
    }
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
};

class ExpNode:public Node{
public:
    string id;
    vector<string> types;
    Node(const string& id,const string& type):Node(),id(id),types(0){
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
