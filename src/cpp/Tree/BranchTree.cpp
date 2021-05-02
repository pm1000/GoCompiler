//
// Created by philipp on 02.05.21.
//

#include "../../header/Tree/BranchTree.h"


BranchTree::BranchTree(Tree *parent) : Tree(parent) {}

BranchTree::~BranchTree() {

}

std::string BranchTree::getName() {
    return name;
}