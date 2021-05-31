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
    this->children.push_back(node);
}

void TreeNode::printTree() {
    cout << "test" << endl;
}

void TreeNode::appendChildrenFromChild(TreeNode *node) {
    vector<TreeNode*> kids = node->getChildren();
    for (unsigned int i = 0; i < kids.size(); ++i){
        children.push_back(kids[i]);
    }
}

const vector<TreeNode *> &TreeNode::getChildren() const {
    return children;
}
