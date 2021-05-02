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
    while(getline(file,line)){
        completeFile += line;
    }

    file.close();
    return completeFile;
}


void IOController::start() {

    for (const auto &file : std::filesystem::directory_iterator(inputDirectory)){
        std::string input = readFile(file.path());
        CompileController* controller = new CompileController();
        controller.start(input);
        writeFile(controller.getTree());
    }

}


void IOController::writeFile(Tree *tree, std::string fileName) {
    fileName = "out_" + fileName;
}