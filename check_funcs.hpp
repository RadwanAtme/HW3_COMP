
#include "hw3_output.cpp"
#include "Classes.h"



bool check_cast(Types type1,Types type2,line_number) {
    if((type1 == Boolean && type2 != Boolean) || (type1 != Boolean && type2 == Boolean))
        return false;

    return true;
}


bool checkInputIsNumber(Types type1,Types type2,yylineno){

    if((type1 != BYTE && type1!= INT)){
        output::errorMismatch(yylineno);
        return false;
    }

    if((type2 != BYTE && type2!= INT)){
        output::errorMismatch(yylineno);
        return false;
    }


    return true;
}

bool checkOneInputIsBool(Types type,yylineno) {
    if (type != Boolean) {
        output::errorMismatch(yylineno);
        return false;
    }
    return true;
}

bool checkInputIsBool(Types type1,Types type2,yylineno){
    if(!checkOneInputIsBool(type1,yylineno))
        return false;

    return checkOneInputIsBool(type2,yylineno);
}
Types getMaxNumbersType(Types type1,Types type2){
        if(type2 == INT)
            return INT;
    return type1;
}



