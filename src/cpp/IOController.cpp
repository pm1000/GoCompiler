//
// Created by philipp on 02.05.21.
//

#include "../header/IOController.h"

IOController::IOController(const std::string &inputDirectory, const std::string &outputDirectory) : inputDirectory(
        inputDirectory), outputDirectory(outputDirectory) {}

IOController::~IOController() {

}

std::string IOController::readFile(std::string path) {

    std::fstream file;
    file.open(path, std::ios::in);

    if (!file.is_open())
        throw std::runtime_error("Unable to open the file " + inputDirectory + "/" + path);

    std::string completeFile;
    std::string line;
    while(getline(file,line, '\n')){
        completeFile += line + '\n';
    }

    file.close();
    return completeFile;
}


void IOController::start() {

    for (const auto &file : std::filesystem::directory_iterator(inputDirectory)){
        // Log the current file
        std::cout << "Current File: " << file.path() << std::endl;
        std::string input = readFile(file.path());

        // Start compiling
        CompileController* controller = new CompileController();
        controller->init(input);
        controller->start();

        // Prepare Console output
        std::cout << "Abstract Syntax Tree:" << std::endl;
        writeFile(controller->getAstRoot(), file.path());
        std::cout << "Symbol Table Tree:" << std::endl;
        writeFile(controller->getSymbolTableRoot(), file.path());
        std::cout << std::endl << std::endl;

        // Remove controller
        delete controller;
    }

}


void IOController::writeFile(Tree *tree, std::string fileName) {

    std::string newFileName = "out_" + fileName;
    std::vector<std::string> output = printTreeRecursive(tree);

    for (std::string &tmp : output) {
        std::cout << tmp << std::endl;
    }
}


std::vector<std::string> IOController::printTreeRecursive(Tree* current) {

    // Helper vector, for each line one string.
    std::vector<std::string> output;

    // Print the current node.
    std::string currentNodeString = current->getName();
    if (current->getChildrenSize() > 0) {
        currentNodeString += " ->";
    }
    output.push_back(currentNodeString);

    // Print all child notes.
    for (int i = 0; i < current->getChildrenSize(); i++) {
        for (std::string &childStrings : printTreeRecursive(current->getChildAt(i))) {
            output.push_back("\t" + childStrings);
        }
    }

    // Return the string created.
    return output;
}