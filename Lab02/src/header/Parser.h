//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_PARSER_H
#define Y_RASTER_A_PARSER_H

#include <stdexcept>

#include "TreeNode.h"

class Parser {
private:
    TreeNode* currentBranch;
    TreeNode* currentScope;

public:
    Parser(std::string content);
    virtual ~Parser();

    void parse();
    TreeNode* getAstRoot();
    TreeNode* getSymbolTableRoot();
};


#endif //Y_RASTER_A_PARSER_H
