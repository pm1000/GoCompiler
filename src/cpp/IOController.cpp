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

    for (const auto &file : std::filesystem::directory_iterator(inputDirectory + "/")){
        std::string input = readFile(file.path());
        CompileController* controller = new CompileController();
        controller->init(input);
        controller->start();
        writeFile(controller->getAstRoot(), file.path());
        writeFile(controller->getSymbolTableRoot(), file.path());
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