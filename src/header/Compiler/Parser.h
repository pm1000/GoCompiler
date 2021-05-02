//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_PARSER_H
#define Y_RASTER_A_PARSER_H


#include "../Tree/Tree.h"
#include "../Tree/BranchTree.h"

class Parser {
private:
    Tree* astRoot = new BranchTree(nullptr);
    Tree* symbolTableRoot = new BranchTree(nullptr);


public:
    Parser();
    virtual ~Parser();

    void parse(std::string content);

    Tree* getAstRoot();
    Tree* getSymbolTableRoot();
};


#endif //Y_RASTER_A_PARSER_H
