//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_IOCONTROLLER_H
#define Y_RASTER_A_IOCONTROLLER_H

#include "iostream"
#include "string"
#include "fstream"
#include "Compiler/CompileController.h"
#include "Tree/Tree.h"
#include "filesystem"

class IOController {
private:
    std::string inputDirectory;
    std::string outputDirectory;

    std::string readFile(std::string path);

    std::vector<std::string> printTreeRecursive(Tree* current);

public:
    IOController(const std::string &inputDirectory, const std::string &outputDirectory);
    virtual ~IOController();

    void start();
    void writeFile(Tree* current, std::string fileName);
};


#endif //Y_RASTER_A_IOCONTROLLER_H
