%{
    #include <iostream>
    using namespace std;
    // global value for int tokens
    int yylval = 0;

    typedef enum {
        ASSIGN, NUMBER, PACKAGE, FUNC, VAR, ENDSTATEMENT, ID,
        OPENPARENT, CLOSEPARENT, OPENCURLY, CLOSECURLY, RELOP, SCOPE,
        UNKNOWN=999, FINISHED=999999 } tokenType;

    int installID();
    int installNum();
%}

delim   [ \t\n]
ws      {delim}+
letter  [A-Za-z]
digit   [0-9]
id      {letter}({letter}|{digit}|[_])*
number  [+-]?{digit}+[.]?{digit}*

%%

{ws}        {/* no action and no return*/}
package     {return(PACKAGE);}
func        {return(FUNC);}
var         {return(VAR);}
{id}        {yylval = (int) installID(); return(ID);}
{number}    {yylval = (int) installNum(); return(NUMBER);}
"("         {yylval = OPENPARENT; return(RELOP);}
")"         {yylval = CLOSEPARENT; return(RELOP);}
"{"         {yylval = OPENCURLY; return(SCOPE);}
"}"         {yylval = CLOSECURLY; return(SCOPE);}
"="         {return(ASSIGN);}
";"         {return(ENDSTATEMENT);}
.           {cout <<"Unknown character[" << yytext[0] << "] \n"; return(UNKNOWN);}
<<EOF>>     {return FINISHED;}

%%

int installID(){
    cout << "ID found " << yylval << endl;
    return 0;
}

int installNum(){
    cout << "NUM found " << yylval << endl;
    return 0;
}

int yywrap(void) {
    return 1;
}

int main( int argc, char *argv[] )
{
    yyin = ( ( 2 == argc ) ? fopen( argv[1], "r" ) : stdin );
    /* Call the lexer, then quit. */
    int tok = -1;
    while ( tok != FINISHED ) {
        tok = yylex();
        cout << "Token = " << tok<< ",\t last value of yylval = " << yylval << endl;
    };
    return 0;
}






