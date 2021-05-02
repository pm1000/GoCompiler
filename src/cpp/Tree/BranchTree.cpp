//
// Created by philipp on 02.05.21.
//

#include "../../header/Tree/BranchTree.h"


BranchTree::BranchTree(Tree *parent, std::string name) : Tree(parent) {
    this->name = name;
}

BranchTree::~BranchTree() {

}

std::string BranchTree::getName() {
    return name;
}