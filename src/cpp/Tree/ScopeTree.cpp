//
// Created by yabr on 02.05.21.
//

#include "../../header/Tree/ScopeTree.h"

ScopeTree::ScopeTree(Tree *parent, std::string name) : Tree(parent) {
    this->name = name;
}

ScopeTree::~ScopeTree() {}

std::string ScopeTree::getName() {
    return "SCOPE_<" + this->name + ">";
}
