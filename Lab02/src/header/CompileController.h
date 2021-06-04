//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_COMPILECONTROLLER_H
#define Y_RASTER_A_COMPILECONTROLLER_H


#include <string>
#include <iostream>

#include "TreeNode.h"

class CompileController {
private:
    std::string content = "";
    TreeNode* astRoot = nullptr;
    TreeNode* symbolTableRoot = nullptr;

public:
    CompileController();

    virtual ~CompileController();

    void init(std::string content);
    void start();


    TreeNode* getAstRoot();
    TreeNode* getSymbolTableRoot();

};


#endif //Y_RASTER_A_COMPILECONTROLLER_H
