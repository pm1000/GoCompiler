//
// Created by yabr on 02.05.21.
//

#ifndef Y_RASTER_A_SCOPETREE_H
#define Y_RASTER_A_SCOPETREE_H


#include <unordered_map>
#include "Tree.h"
#include "SymbolTree.h"

class ScopeTree : public Tree {
private:


public:
    ScopeTree(Tree *parent, std::string name);
    virtual ~ScopeTree();

    std::string getName() override;

};


#endif //Y_RASTER_A_SCOPETREE_H
