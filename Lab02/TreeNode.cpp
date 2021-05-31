//
// Created by philipp on 31.05.21.
//

#include "TreeNode.h"

TreeNode::TreeNode(Type type, string value) {
    type = type;
    value = value;
}

TreeNode::TreeNode(Type type, double number) {
    type = type;
    number = number;
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
    std::string currentNodeString =  std::to_string(getType());
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
    std::string currentNodeString = std::to_string(current->getType());
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
