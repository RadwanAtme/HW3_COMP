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
typedef std::vector<string>::iterator iter_type;


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
    bool IsFunc;
    Scope(bool is_while = 0, bool IsFunc = 0): v(vector<SymTableCell>()){
        Iswhile = is_while;
    }
};



class ScopeList{
    vector<Scope> scopes_list;
    vector<int> scopes_offset;
    bool is_while;

public:

    void openScope(){

        scopes_list.push_back(Scope());
    }
    void closeScope(SymTable table){
        for( auto it::scopes_list){

        }

        table.remove();
        scopes_list.pop();
    }
    void openWhileScope(){

        scopes_list.push_back(Scope(1));
        is_while = 1;

    }
    bool checkIfWhileScope(){
        return is_while;

    }

    void openFuncScope(string RetType,vector<string> id_list,vector<string> types, vector<int> isConst){

        scopes_list.puch_back(Scope());
        iter_type it = id_list.begin();
        iter_type j = types.begin();
        typedef std::vector<int>::iterator t = isConst.begin();
        int k =-1;

        for ( ; it != id_list.end() && j != types.end();++it ++j --k ++t){
            scopes_list.back().v.push_back(SymTableCell(*it, *j, k, *t));
        }

        scopes_offset.push_back(scopes_offset.back());
    }
    void checkVoidReturnType(yylineno y){

    }
    ~ScopeList(){
        std::vector<Scope>::iterator it;
          it = scopes_list.begin();


        for ( ; it != scopes_list.end(); ++it){
            std::vector<SymTableCell>::iterator j;
            j = it->v.begin();
            for(; j != it->v.end() ; ++j){
                output::endScope();
                output::printID(j->id, j->offset, j->type);

            }

        }

    }
};



class Node {
    string id;
    Types type;
};
class Num : public Node {
public:
    int value;

    Num(const string &id, const string &type, int value) : Node(id, type), value(value) {}
};
class Boolean : public Node {
public:
    bool value;

    Boolean(const string &id, const string &type, bool value) : Node(id, type), value(value) {}
};


#endif //HW3_OUTPUT_CPP_CLASSES_H
