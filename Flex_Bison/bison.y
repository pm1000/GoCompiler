%{
	#include <ctype.h>
	#include <stdio.h>
	#include <string>

	#include "TreeNode.h"
	#include "lexer.h"
	#include "parser.h"

	using namespace std;

	#define YYSTYPE double

	int yyerror(TreeNode **treeNodeRoot, yyscan_t scanner, const char *msg) {
            /* Add error handling routine as needed */
        }


    	TreeNode *currentScope = nullptr;
    	string text;

%}

%code requires {
  typedef void* yyscan_t;
}

%output "parser.c"
%defines "parser.h"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { TreeNode **treeNodeRoot }
%parse-param { yyscan_t scanner }


%union {
    int value;
    TreeNode *treeNodeRoot;
}



%right ASSIGN		"="

%token <value> NUMBER 	"number"
%token PACKAGE 		"PACKAGE"
%token <text> ID
%token FUNC 		"FUNC"
%token OPENPARENT	"("
%token CLOSEPARENT	")"
%token OPENCURLY	"{"
%token CLOSECURLY	"}"
%token ENDSTATEMENT	";"
%token VAR		"var"

%type <treeNodeRoot> SCOPE
%type <treeNodeRoot> EXPRESSION
%type <treeNodeRoot> EXPRESSIONS
%type <treeNodeRoot> FUNCTION

%%
START		: PACKAGE_INCLUDE FUNCTIONS		{ treeNodeRoot = createTreeNode(_ROOT, "");}
		;
FUNCTIONS	: FUNCTION FUNCTIONS			{ treeNodeRoot->children.push_back($1); }
		| FUNCTION				{ treeNodeRoot->children.push_back($1); }
		;
PACKAGE_INCLUDE : PACKAGE ID				{ TreeNode* tmp = createTreeNode(_PACKAGE_INCLUDE, "");
								tmp->chidlren.push_back(createTreeNode(_PACKAGE, ""));
								tmp->chidlren.push_back(createTreeNode(_ID, $2));
								treeNodeRoot->children.push_back(tmp); }
		;
FUNCTION	: FUNC ID OPENPARENT CLOSEPARENT SCOPE	{ TreeNode* tmp = createTreeNode(_FUNCTION, "");
								tmp->chidlren.push_back(createTreeNode(_FUNC, ""));
								tmp->chidlren.push_back(createTreeNode(_ID, $2));
								tmp->chidlren.push_back(createTreeNode(_OPENPARENT, ""));
								tmp->chidlren.push_back(createTreeNode(_CLOSEPARENT, ""));
								tmp->chidlren.push_back($5);
								$$ = tmp; }
		;
SCOPE 		: OPENCURLY EXPRESSIONS CLOSECURLY	{ TreeNode* tmp = createTreeNode(_SCOPE, "");
								tmp->push_back(_OPENCURLY, "");
                                                          	currentScope = tmp;
                                                          	tmp->push_back(_EXPRESSIONS, $2);
                                                          	tmp->push_back(_CLOSECURLY, "");
                                                          	$$ = tmp;}
		;
EXPRESSIONS	: EXPRESSION EXPRESSIONS		{ currentScope->push_back($1); }
		| EXPRESSION				{ currentScope->push_back($1); }
		| 					{}
		;
EXPRESSION	: VAR ID ASSIGN NUMBER			{ TreeNode* node = createTreeNode(_EXPRESSION, $4); $$ = node;}
		;

