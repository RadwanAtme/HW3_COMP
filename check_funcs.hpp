#ifndef HW3_CHECK_FUNCS_H
#define HW3_CHECK_FUNCS_H

#include "hw3_output.hpp"
#include <string>
using std::string;


bool check_cast(string type1,string type2,int yylineno);
void checkByte(string id,int yylineno);
bool checkInputIsNumber(string type1,string type2,int yylineno);
bool checkOneInputIsBool(string ret_type, string type,string id,int yylineno);

bool checkInputIsBool(string type1,string type2,int yylineno);
string getMaxNumbersType(string type1,string type2);

bool checkNotConst(bool is_const,int yylineno);

#endif //HW3_OUTPUT_CPP_CLASSES_H



