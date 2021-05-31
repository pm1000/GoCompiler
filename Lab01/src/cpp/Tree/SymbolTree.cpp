//
// Created by yabr on 02.05.21.
//

#include "../../header/Tree/SymbolTree.h"

SymbolTree::SymbolTree(Tree *parent, std::string name) : Tree(parent) {
    this->name = name;
}

SymbolTree::~SymbolTree() {}

std::string SymbolTree::getName() {
    return "Symbol_<" + this->name + ">";
}

void SymbolTree::addChild(Tree *node) {

    Tree::addChild(node);
}
