//
// Created by philipp on 02.05.21.
//

#include "../../header/Compiler/CompileController.h"

CompileController::CompileController() = default;

CompileController::~CompileController() = default;

void CompileController::init(std::string content) {
    this->content = content;
}

void CompileController::start() {

    // Start Phase 1: Parser
    Parser p;
    p.parse(this->content);
    this->astRoot = p.getAstRoot();
    this->symbolTableRoot = p.getSymbolTableRoot();

}

Tree *CompileController::getAstRoot() {
    return this->astRoot;
}

Tree *CompileController::getSymbolTableRoot() {
    return this->symbolTableRoot;
}
