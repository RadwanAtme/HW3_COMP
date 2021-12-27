
#include "hw3_output.cpp"
#include "Classes.h"
#include <string>
using std::string;


bool check_cast(string type1,string type2,line_number) {
    if((type1 == "Boolean" && type2 != "Boolean") || (type1 != "Boolean" && type2 == "Boolean"))
        exit(-1);

    return true;
}


bool checkInputIsNumber(string type1,string type2,yylineno){

    if((type1 != "BYTE" && type1!= "INT")){
        output::errorMismatch(yylineno);
        exit(-1);
    }

    if((type2 != "BYTE" && type2!= "INT")){
        output::errorMismatch(yylineno);
        exit(-1);
    }


    return true;
}

bool checkOneInputIsBool(string type,yylineno) {
    if (type != "BOOL") {
        output::errorMismatch(yylineno);
        exit(-1);
    }
    return true;
}

bool checkInputIsBool(string type1,string type2,yylineno){
    checkOneInputIsBool(type1,yylineno);
    return checkOneInputIsBool(type2,yylineno);
}
Types getMaxNumbersType(string type1,string type2){
        if(type2 == "INT")
            return "INT";
    return type1;
}



