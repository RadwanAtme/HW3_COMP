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



struct SymTableCell {
    string type;
    string name;
    int offest ;
    bool is_const;
};

class SymTable{
    list<vector<SymTableCell>> Stacktable;
    vector<int> offsets;
    unordered_map<string,SymTableCell> All_ids;

public:
    void insertToSymTable(string id,string type,bool is_const){

    }

    bool CheckMain{

    };
 bool   checkDoubleDecleration(string id){
        return All_ids.contains(id);
    };
    void insertFunc(type1,type2,type){

    }
    getElementType  (/**the type of the last element*/)
    getFunRetVal

    void openScope(){
        Stacktable.push_back(new vector<SymTableCell>);
        vector.push_back(vector.back());
    }
    bool checkNotConst(string id, yylineno lineno){
        if(All_ids.contains(id)){
            return All_ids[id].is_const;

        }
        output::errorUndef(lineno);
        exit(-1);

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
