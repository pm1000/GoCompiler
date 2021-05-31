//
// Created by philipp on 02.05.21.
//

#include "../../header/Tree/BranchTree.h"


BranchTree::BranchTree(Tree *parent, std::string name) : Tree(parent) {
    this->name = name;
}

BranchTree::~BranchTree() {
    for (int i = children.size() - 1; i >= 0; --i)
        delete children[i];
}

std::string BranchTree::getName() {
    return name;
}