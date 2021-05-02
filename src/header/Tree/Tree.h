//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_TREE_H
#define Y_RASTER_A_TREE_H

#include "vector"
#include "string"

class Tree {
protected:
    std::vector<Tree*> children;
    Tree* parent;
    std::string name;

public:

    Tree();
    Tree(Tree* parent);
    virtual ~Tree();
    virtual int getChildrenSize() const;
    virtual Tree* getChildAt(int pos) const;
    virtual void addChild(Tree* node);
    virtual Tree* getLastChild() const;
    virtual std::string getName() = 0;
    Tree *getParent() const;
    void setParent(Tree* value);


};


#endif //Y_RASTER_A_TREE_H
