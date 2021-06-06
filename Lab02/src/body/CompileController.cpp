//
// Created by philipp on 02.05.21.
//

#include "../header/CompileController.h"



/**
 *
 */
CompileController::CompileController() = default;



/**
 *
 */
CompileController::~CompileController() = default;



/**
 *
 */
void CompileController::init(std::string filePath) {
    this->filePath = filePath;
}



/**
 *
 */
void CompileController::start() {

    // ################################################################################
    // Start Phase 1+2: Parser+Syntax
    driver drv;

    drv.file = this->filePath;

    // Change logging
    drv.trace_parsing = this->logging;
    drv.trace_scanning = this->logging;

    drv.parse(drv.file);
    this->astRoot = drv.root;


    // ################################################################################
    // Start Phase 3: Semantic
    SemanticCheck* semanticCheck = new SemanticCheck(this->astRoot);
    try {
        semanticCheck->checkTree();
        this->symbolTable = semanticCheck->getSymbolTree();
    } catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    delete semanticCheck;
}



/**
 *
 */
TreeNode *CompileController::getAstRoot() {
    return this->astRoot;
}



/**
 *
 */
TreeNode *CompileController::getSymbolTableRoot() {
    return this->symbolTableRoot;
}



/**
 *
 */
void CompileController::setLogging(bool value) {
    this->logging = value;
}
