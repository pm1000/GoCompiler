//
// Created by yabr on 16.05.21.
//

#include "parser.h"
#include "lexer.h"
#include "TreeNode.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int yyparse (TreeNode **treeNodeRoot, yyscan_t scanner);


void evaluate(TreeNode *e)
{
    switch (e->type) {
        case NUMBER: case ID: cout << e->value << endl; return;
        default: for (TreeNode* tmp : e->children) { evaluate(tmp); }
    }
}



TreeNode *getAST(const char *expr)
{
    TreeNode *treeNodeRoot;
    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        /* could not initialize */
        return NULL;
    }

    state = yy_scan_string(expr, scanner);

    if (yyparse(&treeNodeRoot, scanner)) {
        /* error parsing */
        return NULL;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    return treeNodeRoot;
}



int main(void) {
    char test[] = "package main\n"
                  "\n"
                  "func main(){\n"
                  "\n"
                  "}";
    TreeNode *e = getAST(test);
    evaluate(e);

    return 0;
}