//
// Created by philipp on 02.05.21.
//

#include "../header/IOController.h"

IOController::IOController(const std::string &inputDirectory, const std::string &outputDirectory) : inputDirectory(
        inputDirectory), outputDirectory(outputDirectory) {}

IOController::~IOController() {

}

void IOController::start() {

    for (const auto &file : std::filesystem::directory_iterator(inputDirectory)){
        // Log the current file
        std::cout << "Current File: " << file.path() << std::endl;

        // Start compiling
        CompileController* controller = new CompileController();
        controller->init(file.path().string());
        controller->start();

        if (controller->getAstRoot()) {
            // Prepare Console output
            std::cout << "Abstract Syntax Tree:" << std::endl;
            writeFile(controller->getAstRoot(), file.path().string(), "out_");
            //std::cout << "Symbol Table Tree:" << std::endl;
            //writeFile(controller->getSymbolTableRoot(), file.path().string(), "symbol_");
            std::cout << std::endl << std::endl;
        }

        // Remove controller
        delete controller;
    }

}

void IOController::writeFile(TreeNode *tree, std::string fileName, std::string prefix) {

    std::size_t pos = fileName.find_last_of('/');
    std::string newFileName = outputDirectory + prefix + fileName.substr(pos + 1, fileName.length() - pos - 3) + "txt";
    std::vector<std::string> output = printTreeRecursive(tree);
    try {
        std::fstream file;
        file.open(newFileName, std::ios::out);
        if (!file)
            throw std::runtime_error("Error while creating the file: " + newFileName);

        for (std::string &tmp : output) {
            std::cout << tmp << std::endl;
            file << tmp + "\n";
        }

        file.close();
    }catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}


std::vector<std::string> IOController::printTreeRecursive(TreeNode* current) {

    // Helper vector, for each line one string.
    std::vector<std::string> output;

    // Print the current node.
    std::string currentNodeString = current->getTypeName();
    if (current->getChildren().size() > 0) {
        currentNodeString += " ->";
    }
    output.push_back(currentNodeString);

    // Print all child notes.
    for (int i = 0; i < current->getChildren().size(); i++) {
        for (std::string &childStrings : printTreeRecursive(current->getChildren().at(i))) {
            output.push_back("\t" + childStrings);
        }
    }

    // Return the string created.
    return output;
}