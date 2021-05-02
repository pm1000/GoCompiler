//
// Created by philipp on 02.05.21.
//

#include "../../header/Tree/Tree.h"

Tree::Tree() {
    this->parent = nullptr;
}

Tree::Tree(Tree* parent) {
    this->parent = parent;
}

Tree::~Tree() {
    for (int i = children.size() - 1; i >= 0; --i){
        delete children[i];
    }
}

Tree *Tree::getLastChild() const {
    if (children.size() == 0)
        return nullptr;
    return children[children.size() - 1];
}

void Tree::addChild(Tree *node) {
    children.push_back(node);
}

Tree *Tree::getChildAt(int pos) const {
    if (pos >= children.size())
        return nullptr;
    return children[pos];
}

int Tree::getChildrenSize() const {
    return children.size();
}

Tree *Tree::getParent() const {
    return parent;
}

void Tree::setParent(Tree *value) {
    this->parent = value;
}
