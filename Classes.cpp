#include "Classes.hpp"
void SymTable::checkMain(){
    if(table.find("main")==table.end()){
        output::errorMainMissing();
        exit(-1);
    }else{
        if(table.find("main")->second.type!="void"){
            output::errorMainMissing();
            exit(-1);
        }
    }
}

void SymTable::checkDoubleDecleration(string id, int yylineno) {
    if(table.find(id)!=table.end()){
        output::errorDef(yylineno,id);
    }
}

void SymTable::insertFunc(string id, string ret_type, vector<string> arg_types) {
    SymTableCell cell(id,ret_type,arg_types);
    table.insert(std::make_pair(id,cell));
}

void SymTable::insertToSymTable(string id, string type, bool is_const) {
    SymTableCell cell(id,type,is_const);
    table.insert(std::make_pair(id,cell));
}

void SymTable::checkNotConst(string id,int yylineno){
    if(table.find(id)->second.is_const){
        output::errorConstMismatch(yylineno);
        exit(-1);
    }
}

void SymTable::checkElementExists(string id, int yylineno) {
    if(table.find(id)==table.end()){
        output::errorUndef(yylineno,id);
        exit(-1);
    }
}

string SymTable::getElementType(string id) {
    return table.find(id)->second.type;
}

void SymTable::checkFunction(string id, vector<string> types, int yylineno) {
    checkElementExists(id,yylineno);
    if(!(table.find(id)->second.arg_types==types)){
        output::errorPrototypeMismatch(yylineno,id,types);
    }
}

void SymTable::remove(string id) {
    table.erase(id);
}