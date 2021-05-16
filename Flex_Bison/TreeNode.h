//
// Created by yabr on 16.05.21.
//

#ifndef Y_RASTER_A_TREENODE_H
#define Y_RASTER_A_TREENODE_H

#include <string>
#include <vector>

using namespace std;


// All token types
typedef enum tagTokenType {
    _ROOT,
    _PACKAGE_INCLUDE,
    _FUNCTION,
    _EXPRESSIONS,
    _ASSIGN,
    _NUMBER,
    _PACKAGE,
    _FUNC,
    _VAR,
    _ENDSTATEMENT,
    _ID,
    _OPENPARENT,
    _CLOSEPARENT,
    _OPENCURLY,
    _CLOSECURLY,
    _RELOP,
    _SCOPE
} tokenType;


// TreeNode definition
typedef struct tagTreeNode {

    // The type of the token
    tokenType type;

    // The value for the token
    string value;

    // Children for this token
    vector<tagTreeNode*> children;
} TreeNode;


// Functions
TreeNode *createTreeNode(tokenType type, string value);

#endif //Y_RASTER_A_TREENODE_H
