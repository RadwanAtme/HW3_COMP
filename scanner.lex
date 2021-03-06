%{
#include "Classes.hpp"
#include "parser.tab.hpp"
%}

%option yylineno
%option noyywrap
Sc (;)
Comma (,)
Lparen \(
Rparen \)
Lbrace \{
Rbrace \}
Assign (=)

Id [a-zA-Z][a-zA-Z0-9]*
Number ([1-9][0-9]*|0) 
String \"([^\n\r\"\\]|\\[rnt\"\\])+\"

LineBreak (\n|\r|\r\n)




%%
void 		{yylval=new TypeNode("VOID"); return VOID;}		
int 		{yylval=new TypeNode("INT"); return INT;}
byte 		{yylval=new TypeNode("BYTE"); return BYTE;}
b 			{yylval=new ExpNode("","BYTE"); return B;}
const 		{yylval=new ConstNode(true); return CONST;}
bool 		{yylval=new TypeNode("BOOL"); return BOOL;}
and return AND;
or return OR;
not return NOT;
true 		{yylval=new ExpNode("","BOOL"); return TRUE;}
false 		{yylval=new ExpNode("","BOOL"); return FALSE;}
return return RETURN;
if return IF;
else return ELSE;
while return WHILE;
break return BREAK;
continue return CONTINUE;

\+ return ADD;
\- return MINUS;
\* return MUL;
\/ return DIV;

(==) return IS_EQUAL;
(!=) return NOT_EQUAL;
(<=) return SMALLER_EQUAL;
(>=) return BIGGER_EQUAL;
(<) return SMALLER;
(>) return BIGGER;

{Sc} return SC;
{Comma} return COMMA;
{Lparen} return LPAREN;
{Rparen} return RPAREN;
{Lbrace} return LBRACE;
{Rbrace} return RBRACE;
{Assign} return ASSIGN;

{Id} 		{yylval=new ExpNode(yytext,"ID");  return ID;}
{Number} 	{yylval=new ExpNode(yytext,"INT"); return NUM;}
{String} 	{yylval=new ExpNode(yytext,"STRING"); return STRING;}
{LineBreak} { };
[ \t\s]+ /* eat up whitespace */
\/\/[^\r\n]*[\r|\n|\r\n]? /* eat up comments */

. output::errorLex(yylineno);exit(0);
%%