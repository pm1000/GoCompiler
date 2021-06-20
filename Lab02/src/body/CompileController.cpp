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

        //code generation
        LLVMContext context;
        module = new Module(this->filePath, context);

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
SymbolTree *CompileController::getSymbolTableRoot() {
    return this->symbolTable;
}



/**
 *
 */
void CompileController::setLogging(bool value) {
    this->logging = value;
}

void CompileController::astDFS(TreeNode *node) {
    if (node != nullptr) {
        if (node->getType() == FUNCTION) {
            auto children = node->getChildren();
            if (children.size() == 0) {
                std::cerr <<"Expected a function" << endl;
                node = nullptr;
            } else {
                //build function def
                int pos = 0;
                Function* func = buildFunc(node, children, &pos);
                if (children[pos]->getType() == SCOPE) {
                    auto scopeKids = children[pos]->getChildren();
                    int scopePos = 0;
                    buildScope(children[pos], scopeKids, &scopePos, nullptr);
                }
            }
        }
    }
}

Function* CompileController::buildFunc(TreeNode* parent, vector<TreeNode *> children, int *pos) {
    llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context),false);
    string id = parent->getFunctionID();
    while (*pos < children.size() && children[*pos]->getType() != SCOPE) {
        *pos = *pos + 1;
    }
    return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, id, module);
}

void CompileController::buildScope(TreeNode *parent, vector<TreeNode *> children, int *pos, BasicBlock *current,
                                   Function* f) {
    while (*pos < children.size()) {

        if (children[*pos]->getType() == LCURLY) {
            if (current == nullptr) {
                //standart block
                current = BasicBlock::Create(context, "Scope",f);
            } else {
                //nested blocks
                BasicBlock* nestedBlock = BasicBlock::Create(context,"Scope",f, current);
                buildScope(parent, children, pos, nestedBlock, f);
            }
        }

        if (children[*pos]->getType() == RCURLY) {
            return;
        }

        if (children[*pos]->getType() == EXPRESSION) {

        }

        *pos = *pos + 1;
    }
}

