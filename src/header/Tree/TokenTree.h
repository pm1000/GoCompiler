//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_TOKENTREE_H
#define Y_RASTER_A_TOKENTREE_H

#include "Tree.h"
#include <stdexcept>


class TokenTree : public Tree{
public:
    TokenTree(Tree *parent, std::string name);
    ~TokenTree() override;

    int getChildrenSize() const override;
    Tree *getChildAt(int pos) const override;
    void addChild(Tree *node) override;
    Tree *getLastChild() const override;
    std::string getName() override;
};


#endif //Y_RASTER_A_TOKENTREE_H
