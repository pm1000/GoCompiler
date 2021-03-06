// See https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Parser.html
%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.5"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  #include "../src/header/TreeNode.h"
  class TreeNode;
  # include <string>
  class driver;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
#include "../src/header/driver.hh"
}

%define api.token.prefix {TOK_}
%token
  EOF  0    "end of file"
  ASSIGN    "="
  LPAREN    "("
  RPAREN    ")"
  LCURLY    "{"
  RCURLY    "}"
  PACKAGE   "package"
  FUNC      "func"
  VAR       "var"
  SEMICOLON ";"
  PLUS      "+"
;

%token <std::string> IDENTIFIER "id"
%token <double> NUMBER "number"
%nterm <TreeNode*> START
%nterm <TreeNode*> PACKAGE_INCLUDE
%nterm <TreeNode*> FUNCTIONS
%nterm <TreeNode*> FUNCTION
%nterm <TreeNode*> SCOPE
%nterm <TreeNode*> EXPRESSIONS
%nterm <TreeNode*> EXPRESSION

%printer { yyo << $$; } <*>;

%%

//appendChildrenFromChild
%start START;
START   :   PACKAGE_INCLUDE FUNCTIONS {TreeNode* node = new TreeNode(START);
                                       node->addChild($1); node->appendChildrenFromChild($2);
                                       drv.root = node;
                                       };

PACKAGE_INCLUDE : "package" "id"  {TreeNode* node =  new TreeNode(PACKAGE_INCLUDE);
                                   TreeNode* package = new TreeNode(PACKAGE);
                                   TreeNode* id = new TreeNode(PACKAGE_NAME, $2);
                                   node->addChild(package);
                                   node->addChild(id);
                                   $$ = node;
                                   };

FUNCTIONS : FUNCTION FUNCTIONS {TreeNode * node = new TreeNode(FUNCTION);
                                node->addChild($1);
                                node->appendChildrenFromChild($2);
                                $$ = node;
                                }
    | FUNCTION {TreeNode* node = new TreeNode(FUNCTIONS);
                node->addChild($1);
                $$ = node;
                };


FUNCTION : "func" "id" "(" ")" SCOPE {TreeNode* node = new TreeNode(FUNCTION);
                                        node->addChild(new TreeNode(FUNC));
                                        node->addChild(new TreeNode(ID, $2));
                                        node->addChild(new TreeNode(LPAREN));
                                        node->addChild(new TreeNode(RPAREN));
                                        node->addChild($5);
                                        $$ = node;
                                       };

SCOPE : "{" EXPRESSIONS "}" {TreeNode* node = new TreeNode(SCOPE);
                                node->addChild(new TreeNode(LCURLY));
                                node->appendChildrenFromChild($2);
                                node->addChild(new TreeNode(RCURLY));
                                $$ = node;
                             };

EXPRESSIONS : EXPRESSION EXPRESSIONS {TreeNode* node = new TreeNode(EXPRESSION);
                                       node->addChild($1);
                                       node->appendChildrenFromChild($2);
                                       $$ = node;
                                       }
    | SCOPE EXPRESSIONS {TreeNode* node = new TreeNode(EXPRESSIONS);
                         node->addChild($1);
                         node->addChild($2);
                         $$ = node;
                         }
    | EXPRESSION {TreeNode* node = new TreeNode(EXPRESSIONS);
                  node->addChild($1);
                  $$ = node;}
    | %empty {};

EXPRESSION : "var" "id" "=" "number" {TreeNode* node = new TreeNode(EXPRESSION, 0);
                                      node->addChild(new TreeNode(VAR));
                                      node->addChild(new TreeNode(ID, $2));
                                      node->addChild(new TreeNode(ASSIGN));
                                      node->addChild(new TreeNode(NUMBER, $4));
                                      $$ = node;
                                      }
    | "id" "=" "id" "+" "number" {TreeNode* node = new TreeNode(EXPRESSION, 1);
                                  node->addChild(new TreeNode(ID, $1));
                                  node->addChild(new TreeNode(ASSIGN));
                                  node->addChild(new TreeNode(ID, $3));
                                  node->addChild(new TreeNode(PLUS));
                                  node->addChild(new TreeNode(NUMBER, $5));
                                  $$ = node;
                                  }
    | "id" "=" "number" "+" "id" {TreeNode* node = new TreeNode(EXPRESSION, 2);
                                  node->addChild(new TreeNode(ID, $1));
                                  node->addChild(new TreeNode(ASSIGN));
                                  node->addChild(new TreeNode(NUMBER, $3));
                                  node->addChild(new TreeNode(PLUS));
                                  node->addChild(new TreeNode(ID, $5));
                                  $$ = node;
                                  }
    | "id" "=" "number" {TreeNode* node = new TreeNode(EXPRESSION, 3);
                         node->addChild(new TreeNode(ID, $1));
                         node->addChild(new TreeNode(ASSIGN));
                         node->addChild(new TreeNode(NUMBER, $3));
                         $$ = node;
                         }
    | "id" "=" "id" {TreeNode* node = new TreeNode(EXPRESSION, 4);
                     node->addChild(new TreeNode(ID, $1));
                     node->addChild(new TreeNode(ASSIGN));
                     node->addChild(new TreeNode(ID, $3));
                     $$ = node;
                     }
    | "id" "(" ")" {TreeNode* node = new TreeNode(EXPRESSION, 5);
                    node->addChild(new TreeNode(ID, $1));
                    node->addChild(new TreeNode(LPAREN));
                    node->addChild(new TreeNode(RPAREN));
                    $$ = node;
                    };

%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
