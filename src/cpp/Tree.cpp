//
// Created by philipp on 02.05.21.
//

#include "../header/Tree.h"

Tree::Tree() {}

Tree::~Tree() {

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
