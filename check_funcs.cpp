#include "check_funcs.hpp"
#include <iostream>
#include "Classes.hpp"

bool check_cast(string type1,string type2,int yylineno) {
    if((type1 == "Boolean" && type2 != "Boolean") || (type1 != "Boolean" && type2 == "Boolean")){
        std::cout<<type1<<" "<<type2<<std::endl;
        output::errorMismatch(yylineno);
        exit(-1);
    }

    return true;
}

void checkByte(string id,int yylineno){
    if(std::stoi(id)>255){
        output::errorByteTooLarge(yylineno,id);
        exit(-1);
    }
}
bool checkInputIsNumber(string type1,string type2,int yylineno){

    if((type1 != "BYTE" && type1!= "INT")){
        std::cout<<type1<<" "<<type2<<std::endl;

        output::errorMismatch(yylineno);
        exit(-1);
    }

    if((type2 != "BYTE" && type2!= "INT")){
        std::cout<<type1<<" "<<type2<<std::endl;

        output::errorMismatch(yylineno);
        exit(-1);
    }


    return true;
}

bool checkOneInputIsBool(string ret_type, string type,string id,int yylineno) {
    if (type != "BOOL") {
        if(type == "ID"){
            if(ret_type!="BOOL"){
                std::cout<<ret_type<<std::endl;
                output::errorMismatch(yylineno);
                exit(-1);
            }
        }else{
            output::errorMismatch(yylineno);
            exit(-1);
        }
    }
    return true;
}

bool checkInputIsBool(string type1,string type2,int yylineno){
    if((type1 != "BOOL")||(type2 != "BOOL")){
        output::errorMismatch(yylineno);
        exit(-1);
    }
}
string getMaxNumbersType(string type1,string type2){
    if(type2 == "INT")
        return "INT";
    return type1;
}

bool checkNotConst(bool is_const,int yylineno){
    if(is_const){
        output::errorConstDef(yylineno);
        exit(-1);
    }
}