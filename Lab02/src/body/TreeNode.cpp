//
// Created by philipp on 31.05.21.
//

#include "../header/TreeNode.h"

TreeNode::TreeNode(Type type, string value) {
    this->type = type;
    this->value = value;
}

TreeNode::TreeNode(Type type, double number) {
    this->type = type;
    this->number = number;
}

TreeNode::TreeNode(Type type) {
    this->type = type;
}

TreeNode::~TreeNode() {
    for (unsigned int i = 0; i < children.size(); ++i){
        delete children[i];
    }
}

void TreeNode::addChild(TreeNode *node) {
    if (node) {
        this->children.push_back(node);
    }
}

std::vector<std::string> TreeNode::printTree() {
    // Helper vector, for each line one string.
    std::vector<std::string> output;

    // Print the current node.
    std::string currentNodeString = getTypeName();
    if (children.size() > 0) {
        currentNodeString += " ->";
    }
    output.push_back(currentNodeString);

    // Print all child notes.
    for (int i = 0; i < children.size(); i++) {
        for (std::string &childStrings : printTreeRecursive(children[i])) {
            output.push_back("\t" + childStrings);
        }
    }

    // Return the string created.
    return output;
}

std::vector<std::string> TreeNode::printTreeRecursive(TreeNode* current) {

    // Helper vector, for each line one string.
    std::vector<std::string> output;

    // Print the current node.
    std::string currentNodeString = current->getTypeName();
    std::vector<TreeNode*> kids = current->getChildren();
    if (kids.size() > 0) {
        currentNodeString += " ->";
    }
    output.push_back(currentNodeString);

    // Print all child notes.
    for (int i = 0; i < kids.size(); i++) {
        for (std::string &childStrings : printTreeRecursive(kids[i])) {
            output.push_back("\t" + childStrings);
        }
    }

    // Return the string created.
    return output;
}

void TreeNode::appendChildrenFromChild(TreeNode *node) {
    if (node) {
        vector<TreeNode *> kids = node->getChildren();
        for (unsigned int i = 0; i < kids.size(); ++i) {
            children.push_back(kids[i]);
        }
    }
}

const vector<TreeNode *> &TreeNode::getChildren() const {
    return children;
}

Type TreeNode::getType() const {
    return type;
}

const string &TreeNode::getValue() const {
    return value;
}

double TreeNode::getNumber() const {
    return number;
}

/*
 * enum Type{NUMBER = 0, PACKAGE = 1, FUNC = 2, VAR = 3, SEMICOLON = 4, ASSIGN = 5, LPAREN = 6, RPAREN = 7, LCURLY = 8,
            RCURLY = 9, _EOF = 10, ID = 11, PACKAGE_INCLUDE = 100, START = 101, SCOPE = 102, EXPRESSION = 103,
            FUNCTIONS = 104, FUNCTION = 105, EXPRESSIONS = 106};

 */
string TreeNode::getTypeName() {
    switch (this->type) {
        case NUMBER :
            return "number: " + std::to_string(this->number);
        case PACKAGE :
            return "package";
        case FUNC :
            return "func";
        case VAR :
            return "var";
        case SEMICOLON :
            return "semicolon";
        case ASSIGN :
            return "assign";
        case LPAREN :
            return "lparen";
        case RPAREN :
            return "rparen";
        case LCURLY :
            return "lcurly";
        case RCURLY :
            return "rcurly";
        case _EOF :
            return "eof";
        case ID :
            return "id: " + this->value;
        case PACKAGE_INCLUDE :
            return "package_include";
        case START :
            return "start";
        case SCOPE :
            return "scope";
        case EXPRESSION :
            return "expression";
        case FUNCTIONS :
            return "functions";
        case FUNCTION :
            return "function";
        case EXPRESSIONS :
            return "expressions";
        case PACKAGE_NAME :
            return "package_name: " + this->value;
        default :
            return "error";
    }
}
