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
    cout << "Using File: " << drv.file << endl;

    // Change logging
    drv.trace_parsing = true;
    drv.trace_scanning = true;

    drv.parse(drv.file);
    this->astRoot = drv.root;


    // ################################################################################
    // Start Phase 3: Semantic
    // TODO
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
