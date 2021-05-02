//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_BRANCHTREE_H
#define Y_RASTER_A_BRANCHTREE_H


#include "Tree.h"

class BranchTree : public Tree {
public:
    BranchTree(Tree *parent);

    virtual ~BranchTree();

    std::string getName() override;
};


#endif //Y_RASTER_A_BRANCHTREE_H
