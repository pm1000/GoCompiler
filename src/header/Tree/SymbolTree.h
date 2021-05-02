//
// Created by yabr on 02.05.21.
//

#ifndef Y_RASTER_A_SYMBOLTREE_H
#define Y_RASTER_A_SYMBOLTREE_H


#include "Tree.h"

class SymbolTree : public Tree {
private:

public:
    SymbolTree(Tree *parent, std::string name);
    virtual ~SymbolTree();

    std::string getName() override;

    void addChild(Tree *node) override;
};


#endif //Y_RASTER_A_SYMBOLTREE_H
