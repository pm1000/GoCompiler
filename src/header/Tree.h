//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_TREE_H
#define Y_RASTER_A_TREE_H

#include "vector"


class Tree {
protected:
    std::vector<Tree*> children;

public:

    Tree();
    virtual ~Tree();
    virtual int getChildrenSize() const;
    virtual Tree* getChildAt(int pos) const;
    virtual void addChild(Tree* node);
    virtual Tree* getLastChild() const;


};


#endif //Y_RASTER_A_TREE_H
