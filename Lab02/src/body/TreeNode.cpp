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

bool TreeNode::findChildType(Type t) {
    for (int i = 0; i < children.size(); ++i)
        if (t == children[i]->getType())
            return true;
    return false;
}

string TreeNode::getExpressionID() {
    if (type == EXPRESSION){
        for (int i = 0; i < children.size(); ++i)
            if (children[i]->getType() == ID)
                return children[i]->getValue();
    }
    return string();
}

string TreeNode::getFunctionID() {
    if (type == FUNCTION)
        for (int i = 0; i < children.size(); ++i){
            if (children[i]->getType() == ID)
                return children[i]->getValue();
        }
    return std::string();
}

int TreeNode::getExpressionType() const {
    return expressionType;
}

void TreeNode::setExpressionType(int value) {
    this->expressionType = value;
}

TreeNode *TreeNode::getAssignID() {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getType() == ID) {
            //first id
            return children[i];
        }
    }
    return nullptr;
}

pair<TreeNode *, double> TreeNode::getExpID_Num() {

    bool foundFirst = false;
    pair<TreeNode*, double> p;
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getType() == ID) {
            if (!foundFirst)
                foundFirst = !foundFirst;
            else {
                p.first = children[i];
            }
        }

        if (children[i]->getType() == NUMBER) {
            p.second = children[i]->getNumber();
            break;
        }
    }

    return p;
}

pair<double, TreeNode *> TreeNode::getExpNum_ID() {

    bool foundFirst = false;
    pair<double, TreeNode*> p;
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getType() == ID) {
            if (!foundFirst)
                foundFirst = !foundFirst;
            else {
                p.second = children[i];
                break;
            }
        }

        if (children[i]->getType() == NUMBER) {
            p.first = children[i]->getNumber();
        }
    }

    return p;
}

pair<double, double> TreeNode::getExpNum_Num() {

    pair<double, double> p;
    bool foundFirst = false;

    for (TreeNode* child : children) {
        if (!foundFirst && child->getType() == NUMBER) {
            p.first = child->getNumber();
            foundFirst = true;
        } else if (foundFirst && child->getType() == NUMBER) {
            p.second = child->getNumber();
            return p;
        }
    }

    return p;
}

pair<TreeNode *, TreeNode *> TreeNode::getExpID_ID() {

    // x = y+z --> y_z
    pair<TreeNode *, TreeNode *> p;
    bool foundFirst = false;

    for (TreeNode* child : children) {
        if (!foundFirst && child->getType() == ID) {
            p.first = child;
            foundFirst = true;
        } else if (foundFirst && child->getType() == ID) {
            p.second = child;
            return p;
        }
    }

    return p;
}

TreeNode *TreeNode::getExpID() {

    bool foundFirst = false;
    TreeNode* node = nullptr;
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getType() == ID) {
            if (!foundFirst)
                foundFirst = !foundFirst;
            else {
                node = children[i];
                break;
            }
        }
    }

    return node;
}

double TreeNode::getExpNum() {
    bool foundFirst = false;
    double value = 0.0;

    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->getType() == NUMBER) {
            value = children[i]->getNumber();
            break;
        }
    }

    return value;
}

SymbolTree *TreeNode::getSymbolTreeNode() const {
    return symbolTreeNode;
}

void TreeNode::setSymbolTreeNode(SymbolTree *symbolTreeNode) {
    TreeNode::symbolTreeNode = symbolTreeNode;
}
