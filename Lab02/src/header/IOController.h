//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_IOCONTROLLER_H
#define Y_RASTER_A_IOCONTROLLER_H

#include "iostream"
#include "string"
#include "fstream"
#include "CompileController.h"
#include "TreeNode.h"
#include <filesystem>
#include "Symbol/SemanticCheck.h"

class IOController {
private:
    std::string inputDirectory;
    std::string outputDirectory;
    std::vector<std::string> printTreeRecursive(TreeNode* current);

public:
    IOController(const std::string &inputDirectory, const std::string &outputDirectory);
    virtual ~IOController();

    void start();
    void writeFile(TreeNode* current, std::string fileName, std::string prefix);
};


#endif //Y_RASTER_A_IOCONTROLLER_H
