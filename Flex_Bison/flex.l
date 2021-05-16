%{
    #include <iostream>

    #include "TreeNode.h"
    #include "parser.h"

    using namespace std;

    // global value for int tokens
    int yylval = 0;

    /*typedef enum {
        ASSIGN, NUMBER, PACKAGE, FUNC, VAR, ENDSTATEMENT, ID,
        OPENPARENT, CLOSEPARENT, OPENCURLY, CLOSECURLY, RELOP, SCOPE,
        UNKNOWN=999, FINISHED=999999 } tokenType;*/

%}


delim   [ \t\n]
ws      {delim}+
letter  [A-Za-z]
digit   [0-9]
id      {letter}({letter}|{digit}|[_])*
number  [+-]?{digit}+[.]?{digit}*



%option outfile="lexer.c" header-file="lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd
%option bison-bridge



%%

{ws}        {/* no action and no return*/}
package     {return(PACKAGE);}
func        {return(FUNC);}
var         {return(VAR);}
{id}        {sscanf(yytext, "%s", &yylval->value); return(ID);}
{number}    {sscanf(yytext, "%d", &yylval->value); return(NUMBER);}
"("         {return(OPENPARENT);}
")"         {return(CLOSEPARENT);}
"{"         {return(OPENCURLY);}
"}"         {return(CLOSECURLY);}
"="         {return(ASSIGN);}
";"         {return(ENDSTATEMENT);}
.           {cout <<"Unknown character[" << yytext[0] << "] \n"; return(UNKNOWN);}
<<EOF>>     {return FINISHED;}

%%


int yyerror(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    return 0;
}
