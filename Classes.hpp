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
    void remove(string id); //ok
    ~SymTable()=default;
    SymTable(){
        insertFunc("print","VOID",{"STRING"});
        insertFunc("printi","VOID",{"INT"});
    }
};


class Scope {
public:
    vector<SymTableCell> v ;
    bool Iswhile;
    int num_of_elements;
    bool is_func;
    string ret_type;
    Scope(bool is_while = false): v(0){
        Iswhile = is_while;
        num_of_elements=0;
    }
};


class ScopeList{
    vector<Scope> scopes_list;
    vector<SymTableCell> function_list;
    int offset = 0;
    bool is_while;

public:

    void openScope(){
        scopes_list.push_back(Scope());
    }

    void closeScope(SymTable table){
        Scope scope_to_close = scopes_list.back();
        for(SymTableCell element:scope_to_close.v){
            table.remove(element.id);
        }
        offset -= scope_to_close.num_of_elements;
        scopes_list.pop_back();
    }

    void openWhileScope(){
        scopes_list.push_back(Scope(true));

    }

    bool checkIfWhileScope(string str,int yylineno){
        for(auto element:scopes_list){
            if(element.Iswhile){
                return true;
            }
        }
        if(str=="break"){
            output::errorUnexpectedBreak(yylineno);
        }else{
            output::errorUnexpectedContinue(yylineno);
        }

    }

    void openFuncScope(string RetType,vector<string> id_list,vector<string> types_list, vector<int> is_const_list){
        Scope scope_to_push = Scope(false);
        scope_to_push.is_func = true;
        scope_to_push.ret_type = RetType;
        int var_offset = id_list.size()*-1;
        for(unsigned int i=0;i<id_list.size();i++){
            SymTableCell cell(id_list[i],types_list[i],is_const_list[i]);
            cell.offset = var_offset;
            scope_to_push.v.push_back(cell);
            var_offset++;
        }
        this->scopes_list.push_back(scope_to_push);
    }

    void insertFunc(string id, string ret_type, vector<string> arg_types){
        SymTableCell cell(id,ret_type,arg_types);
        function_list.push_back(cell);
    }

    void printFuncs(){
        output::endScope();
        for(SymTableCell func:function_list){
            std::cout << func.id << " " << output::makeFunctionType(func.type,func.arg_types) <<  " " << 0 <<  endl;
        }
    }

    void insertVar(string id,string type){
        SymTableCell cell(id,type,false);
        cell.offset=this->offset;
        offset++;
        scopes_list.back().v.push_back(cell);
    }
    ScopeList(){
        insertFunc("print","VOID",{"STRING"});
        insertFunc("printi","VOID",{"INT"});
    }
    void checkVoidReturnType(int yylineno){
        for(auto element:scopes_list){
            if(element.is_func){
                if(element.ret_type!="VOID"){
                    output::errorMismatch(yylineno);
                    exit(-1);
                }else{
                    return;
                }
            }
        }
        output::errorMismatch(yylineno);
        exit(-1);
    }
    void checkReturnType(string type,int yylineno){
        for(auto element:scopes_list){
            if(element.is_func){
                if(element.ret_type!=type){
                    output::errorMismatch(yylineno);
                    exit(-1);
                }else{
                    return;
                }
            }
        }
        output::errorMismatch(yylineno);
        exit(-1);
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
    ExpNode(const string& id,const string& type):Node(),id(id),types(0){
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
    void appendIDAndType(string id,string type,bool is_const){
        id_list.push_back(id);
        type_list.push_back(type);
        is_const_list.push_back(is_const);
    }
    void appendIDAndType(vector<string> id,vector<string> type,vector<bool> is_const){
        id_list.insert(id_list.end(),id.begin(),id.end());
        type_list.insert(type_list.end(),type.begin(),type.end());
        is_const_list.insert(is_const_list.end(),is_const.begin(),is_const.end());
    }

};
#endif //HW3_OUTPUT_CPP_CLASSES_H
