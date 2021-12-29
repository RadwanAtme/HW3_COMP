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

void SymTable::checkDoubleDecleration(string& id, int& yylineno) {
    if(table.find(id)!=table.end()){
        output::errorDef(yylineno,id);
    }
}

void SymTable::insertFunc(string id, string ret_type, vector<string> arg_types) {
    SymTableCell cell(id,ret_type,arg_types);
    for(auto e:arg_types){

    }
    for(auto e:cell.arg_types){
    }
    table.insert(std::make_pair(id,cell));
}

void SymTable::insertToSymTable(string& id, string& type, bool& is_const) {
    SymTableCell cell(id,type,is_const);
    table.insert(std::make_pair(id,cell));
}

void SymTable::checkNotConst(string& id,int& yylineno){
    if(table.find(id)->second.is_const){
        output::errorConstMismatch(yylineno);
        exit(-1);
    }
}

void SymTable::checkElementExists(string& id, int& yylineno) {
    if(table.find(id)==table.end()){
        output::errorUndef(yylineno,id);
        exit(-1);
    }
}

string SymTable::getElementType(string& id) {
    return table.find(id)->second.type;
}

void SymTable::checkFunction(string& id, vector<string>& types, int& yylineno) {
    checkElementExists(id,yylineno);
    if(!(table.find(id)->second.arg_types==types)){
        output::errorPrototypeMismatch(yylineno,id,types);
    }
}
void SymTable::checkFunction(string &id, int &yylineno) {
    checkElementExists(id,yylineno);
    if(!(table.find(id)->second.arg_types.empty())){
        vector<string> vec;
        output::errorPrototypeMismatch(yylineno,id,vec);
    }
}
void SymTable::remove(string& id) {
    table.erase(id);
}
SymTable::SymTable(){
    string printo("print");
    string printio("printi");
    string voido("VOID");
    vector<string> v1={"STRING"};
    vector<string> v2={"INT"};
    insertFunc(printo,voido,v1);
    insertFunc(printio,voido,v2);
}

void SymTable::printTable() {
    for (auto const &pair: this->table) {
        std::cout << "{" << pair.first << ": " << pair.second.id <<pair.second.type<< "}\n";
    }
}

SymTableCell::SymTableCell(const SymTableCell &cell):id(cell.id),type(cell.type),offset(cell.offset),
                                                     is_const(cell.is_const),arg_types(cell.arg_types){

}

SymTableCell::SymTableCell(string id,string type,bool is_const):id(id),type(type),offset(0),
                                                                is_const(is_const){
}
SymTableCell::SymTableCell(string id, string ret_type, vector<string> arg_types):id(id),type(ret_type),offset(0),
                                                                                 is_const(false),arg_types(arg_types){
}


// --------------------------------------------------------------------------------------------------------------------
Scope::Scope(bool is_while): v(0){
    Iswhile = is_while;
    num_of_elements=0;
}

void ScopeList::openScope(){
    scopes_list.push_back(Scope());
}

void ScopeList::closeScope(SymTable*& table){
    Scope scope_to_close = scopes_list.back();
    for(SymTableCell element:scope_to_close.v){
        table->remove(element.id);
    }
    offset -= scope_to_close.num_of_elements;
    scopes_list.pop_back();
}

void ScopeList::openWhileScope(){
    scopes_list.push_back(Scope(true));

}

bool ScopeList::checkIfWhileScope(const string& str,int& yylineno){
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

void ScopeList::openFuncScope(SymTable*& table, string& RetType, vector<string>& id_list, vector<string>& types_list,  vector<bool>& is_const_list){
    Scope scope_to_push = Scope(false);
    scope_to_push.is_func = true;
    scope_to_push.ret_type = RetType;
    int var_offset = id_list.size()*-1;
    for(unsigned int i=0;i<id_list.size();i++){
        SymTableCell cell(id_list[i],types_list[i],is_const_list[i]);
        bool is_con = is_const_list[i];
        table->insertToSymTable(id_list[i],types_list[i],is_con);
        cell.offset = var_offset;
        scope_to_push.v.push_back(cell);
        var_offset++;
    }
    this->scopes_list.push_back(scope_to_push);
}

void ScopeList::insertFunc( string id,string ret_type,  vector<string> arg_types){

    SymTableCell cell(id,ret_type,arg_types);
    function_list.push_back(cell);
}

void ScopeList::printFuncs(){
    output::endScope();
    for(SymTableCell func:function_list){
        std::cout << func.id << " " << output::makeFunctionType(func.type,func.arg_types) <<  " " << 0 <<  endl;
    }
}

void ScopeList::insertVar(const string& id,const string& type){
    SymTableCell cell(id,type,false);
    cell.offset=this->offset;
    offset++;
    scopes_list.back().v.push_back(cell);
}

void ScopeList::checkVoidReturnType(const int& yylineno){

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
void ScopeList::checkReturnType(const string& type,const int& yylineno){
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

ScopeList::ScopeList(){
    insertFunc("print","VOID",{"STRING"});
    insertFunc("printi","VOID",{"INT"});
}


TypeNode::TypeNode(const string& type):Node(){
    this->type = type;
}
 string TypeNode::getType(){std::cout<<"error"<<std::endl;}
 void TypeNode::changeType(const string& type){std::cout<<"error"<<std::endl;}
 void TypeNode::appendIDAndType(const string& id,const string& type,const bool& is_const){std::cout<<"error"<<std::endl;}
 void TypeNode::appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const){std::cout<<"error"<<std::endl;}
 void TypeNode::appendVector(const vector<string>& types){std::cout<<"error"<<std::endl;}



ConstNode::ConstNode(bool var):Node(){
    this->is_const = var;
}
 string ConstNode::getType(){std::cout<<"error"<<std::endl;}
 void ConstNode::changeType(const string& type){std::cout<<"error"<<std::endl;}
 void ConstNode::appendIDAndType(const string& id,const string& type,const bool& is_const){std::cout<<"error"<<std::endl;}
 void ConstNode::appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const){std::cout<<"error"<<std::endl;}
 void ConstNode::appendVector(const vector<string>& types){std::cout<<"error"<<std::endl;}



ExpNode::ExpNode(const string& id,const string& type):Node(){
    this->id = id;
    types.push_back(type);
}
 string ExpNode::getType(){
return ExpNode::types[0];
}
 void ExpNode::changeType(const string& type){
types[0]=type;
}
 void ExpNode::appendVector(const vector<string>& types){
this->types.insert(this->types.end(),types.begin(),types.end());
}
 void ExpNode::appendIDAndType(const string& id,const string& type,const bool& is_const){std::cout<<"error"<<std::endl;}
 void ExpNode::appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const){std::cout<<"error"<<std::endl;}




 void FormalsNode::appendIDAndType(const string& id,const string& type,const bool& is_const){
id_list.push_back(id);
type_list.push_back(type);
is_const_list.push_back(is_const);
}
 void FormalsNode::appendIDAndType(const vector<string>& id,const vector<string>& type,const vector<bool>& is_const){
id_list.insert(id_list.end(),id.begin(),id.end());
type_list.insert(type_list.end(),type.begin(),type.end());
is_const_list.insert(is_const_list.end(),is_const.begin(),is_const.end());
}
 string FormalsNode::getType(){std::cout<<"error"<<std::endl;}
 void FormalsNode::changeType(const string& type){std::cout<<"error"<<std::endl;}
 void FormalsNode::appendVector(const vector<string>& types){std::cout<<"error"<<std::endl;}