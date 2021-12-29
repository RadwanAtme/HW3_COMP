#ifndef HW3_OUTPUT_CPP_CLASSES_H
#define HW3_OUTPUT_CPP_CLASSES_H
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include "check_funcs.hpp"
#include "hw3_output.hpp"
#include <iostream>

extern int yylineno;

#define YYSTYPE Node*

using std::string;
using std::vector;
using std::unordered_map;
using std::list;
typedef std::vector<string>::iterator iter_type;

struct SymTableCell {
    string id;
    string type;
    int offset;
    bool is_const;
    vector<string> arg_types;
    SymTableCell(string id, string ret_type, vector<string> arg_types);
    SymTableCell(const SymTableCell& cell);
    SymTableCell(string id,string type,bool is_const);
    SymTableCell()= default;
    ~SymTableCell() = default;
};




class SymTable{
    unordered_map<string,SymTableCell> table;

public:
    void insertToSymTable(string& id,string& type,bool& is_const); // ok

    void checkMain(); // ok
    void checkDoubleDecleration(string& id,int& yylineno); // ok
    void insertFunc(string id,string ret_type,vector<string> arg_types); //ok
    void checkNotConst(string& id,int& yylineno); //ok
    void checkElementExists(string& id,int& yylineno); // ok
    string getElementType(string& id); //ok
    void checkFunction(string& id,vector<string>& types,int& yylineno);//ok
    void checkFunction(string& id,int& yylineno);
    void remove(string& id); //ok
    void printTable();
    ~SymTable()=default;
    SymTable();
};


class Scope {
public:
    vector<SymTableCell> v ;
    bool Iswhile;
    int num_of_elements;
    bool is_func;
    string ret_type;
    explicit Scope(bool is_while = false);
};


class ScopeList{
    vector<Scope> scopes_list;
    vector<SymTableCell> function_list;
    int offset = 0;
    bool is_while;

public:
    void openScope();
    void closeScope(SymTable*& table);
    void openWhileScope();
    bool checkIfWhileScope(const string& str,int& yylineno);
    void openFuncScope( SymTable*& table,string& RetType, vector<string>& id_list, vector<string>& types_list,  vector<bool>& is_const_list);
    void insertFunc( string id,string ret_type,  vector<string> arg_types);
    void printFuncs();
    void insertVar(const string& id,const string& type);
    ScopeList();
    void checkVoidReturnType(const int& yylineno);
    void checkReturnType(const string& type,const int& yylineno);
};


class Node{
public:
    string id;
    string type;
    bool is_const;
    vector<string> types;
    vector<string> id_list;
    vector<string> type_list;
    vector<bool> is_const_list;
    Node()=default;
    virtual string getType()=0;
    virtual void changeType(const string& type)=0;
    virtual void appendIDAndType(const string& id,const string& type,const bool& is_const)=0;
    virtual void appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const)=0;
    virtual void appendVector(const vector<string>& types) = 0;
};

class TypeNode:public Node{
public:
    TypeNode(const string& type);
    virtual string getType()override;
    virtual void changeType(const string& type)override;
    virtual void appendIDAndType(const string& id,const string& type,const bool& is_const)override;
    virtual void appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const)override;
    virtual void appendVector(const vector<string>& types)override;
};

class ConstNode:public Node{
public:
    ConstNode(bool var);
    virtual string getType()override;
    virtual void changeType(const string& type)override;
    virtual void appendIDAndType(const string& id,const string& type,const bool& is_const)override;
    virtual void appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const)override;
    virtual void appendVector(const vector<string>& types)override;

};

class ExpNode:public Node{
public:
    ExpNode(const string& id,const string& type);
    virtual string getType()override;
    virtual void changeType(const string& type)override;
    virtual void appendVector(const vector<string>& types)override;
    virtual void appendIDAndType(const string& id,const string& type,const bool& is_const)override;
    virtual void appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const)override;
};

class FormalsNode:public Node{
public:
    FormalsNode() = default;
    virtual void appendIDAndType(const string& id,const string& type,const bool& is_const)override;
    virtual void appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const)override;
    virtual string getType()override;
    virtual void changeType(const string& type)override;
    virtual void appendVector(const vector<string>& types)override;


};
#endif //HW3_OUTPUT_CPP_CLASSES_H
