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

int TokenTree::getChildrenSize() const {
    return Tree::getChildrenSize();
}

Tree *TokenTree::getChildAt(int pos) const {
    return Tree::getChildAt(pos);
}

void TokenTree::addChild(Tree *node) {
    throw std::runtime_error("Tokens are now allowed to have children");
}

Tree *TokenTree::getLastChild() const {
    return Tree::getLastChild();
}
