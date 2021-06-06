//
// Created by philipp on 31.05.21.
//

#ifndef LAB02_TREENODE_H
#define LAB02_TREENODE_H

#include "vector"
#include "string"
#include "iostream"

using std::endl;
using std::cout;
using std::vector;
using std::string;

enum Type{NUMBER = 0, PACKAGE = 1, FUNC = 2, VAR = 3, SEMICOLON = 4, ASSIGN = 5, LPAREN = 6, RPAREN = 7, LCURLY = 8,
    RCURLY = 9, _EOF = 10, ID = 11, PLUS = 12, PACKAGE_INCLUDE = 100, START = 101, SCOPE = 102, EXPRESSION = 103,
    FUNCTIONS = 104, FUNCTION = 105, EXPRESSIONS = 106};


class TreeNode {
public:
    TreeNode(Type type, string value);
    TreeNode(Type type, double number);
    TreeNode(Type type);
    virtual ~TreeNode();

    void addChild(TreeNode* node);
    void appendChildrenFromChild(TreeNode* node);
    std::vector<std::string> printTree();
    std::vector<std::string> printTreeRecursive(TreeNode* current);
    const vector<TreeNode *> &getChildren() const;

    Type getType() const;
    const string &getValue() const;
    double getNumber() const;
    string getTypeName();
private:
    enum Type type;
    vector<TreeNode*> children;
    string value;
    double number;
    TreeNode* parent;
};


#endif //LAB02_TREENODE_H
