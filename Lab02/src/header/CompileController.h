//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_COMPILECONTROLLER_H
#define Y_RASTER_A_COMPILECONTROLLER_H

#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/ValueHandle.h"

#include <string>
#include <iostream>

#include "TreeNode.h"
#include "../header/driver.hh"
#include "Symbol/SymbolTree.h"
#include "Symbol/SemanticCheck.h"

using llvm::Module;
using llvm::LLVMContext;
using llvm::BasicBlock;
using llvm::Function;
using llvm::Value;
using llvm::Instruction;

class CompileController {
private:
    std::string filePath = "";
    bool logging {false};
    TreeNode* astRoot = nullptr;
    SymbolTree* symbolTable = nullptr;
    Module* module;
    LLVMContext context;
    void astDFS(TreeNode* node, SymbolTree* symbolTree);
    Function* buildFunc(TreeNode* parent, vector<TreeNode*> children, int* pos);
    void buildScope(TreeNode* parent, vector<TreeNode*> children, int* pos, BasicBlock* current, Function* f, bool outRec);

public:
    CompileController();
    virtual ~CompileController();

    void init(std::string content);
    void start();

    void setLogging(bool value);

    TreeNode* getAstRoot();
    SymbolTree* getSymbolTableRoot();

};


#endif //Y_RASTER_A_COMPILECONTROLLER_H
