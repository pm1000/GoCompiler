//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_COMPILECONTROLLER_H
#define Y_RASTER_A_COMPILECONTROLLER_H


#include <string>
#include <iostream>

#include "Parser.h"

class CompileController {
private:
    std::string content = "";
    Tree* astRoot = nullptr;
    Tree* symbolTableRoot = nullptr;

public:
    CompileController();

    virtual ~CompileController();

    void init(std::string content);
    void start();


    Tree* getAstRoot();
    Tree* getSymbolTableRoot();

};


#endif //Y_RASTER_A_COMPILECONTROLLER_H
