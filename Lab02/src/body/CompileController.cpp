//
// Created by philipp on 02.05.21.
//

#include "../header/CompileController.h"

CompileController::CompileController() = default;

CompileController::~CompileController() = default;

void CompileController::init(std::string content) {
    this->content = content;
}

void CompileController::start() {

    // Start Phase 1: Parser
    Parser* p = new Parser(content);
    try {
        p->parse();
    } catch (std::exception &e) {
        std::cout << "[Parsing Error] Error while parsing: " << e.what() << std::endl << "This error occurred in line "
        << p->getLine() << std::endl;
    }

    this->astRoot = p->getAstRoot();
    this->symbolTableRoot = p->getSymbolTableRoot();

    delete p;

}

TreeNode *CompileController::getAstRoot() {
    return this->astRoot;
}

TreeNode *CompileController::getSymbolTableRoot() {
    return this->symbolTableRoot;
}
