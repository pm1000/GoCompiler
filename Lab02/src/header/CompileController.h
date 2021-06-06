//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_COMPILECONTROLLER_H
#define Y_RASTER_A_COMPILECONTROLLER_H


#include <string>
#include <iostream>

#include "TreeNode.h"
#include "../header/driver.hh"
#include "Symbol/SymbolTree.h"
#include "Symbol/SemanticCheck.h"

class CompileController {
private:
    std::string filePath = "";
    bool logging {false};
    TreeNode* astRoot = nullptr;
    SymbolTree* symbolTable = nullptr;

public:
    CompileController();
    virtual ~CompileController();

    void init(std::string content);
    void start();

    void setLogging(bool value);

    TreeNode* getAstRoot();
    SymbolTree* getSymbolTableRoot();

};


#endif //Y_RASTER_A_COMPILECONTROLLER_H
