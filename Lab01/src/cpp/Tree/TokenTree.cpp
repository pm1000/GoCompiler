//
// Created by philipp on 02.05.21.
//

#include "../../header/Tree/TokenTree.h"

TokenTree::TokenTree(Tree *parent, std::string name) {
    this->name = name;
    this->parent = parent;
}

std::string TokenTree::getName() {
    return "TOKEN_<" + name + ">";
}

TokenTree::~TokenTree() {

}

