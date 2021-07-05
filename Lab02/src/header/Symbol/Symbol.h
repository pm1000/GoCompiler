//
// Created by philipp on 06.06.21.
//

#ifndef LAB02_SYMBOL_H
#define LAB02_SYMBOL_H

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

#include <string>
#include <iostream>

using std::string;
using llvm::Module;
using llvm::LLVMContext;
using llvm::BasicBlock;
using llvm::Function;
using llvm::Value;
using llvm::Instruction;

enum SymbolType {SYM_START, SYM_FUNCTION, SYM_VARIABLE};

class Symbol {
private:
    string name;
    SymbolType type;
    bool declared;
    llvm::AllocaInst* alloc;
    llvm::Function* func;

public:
    Symbol(const string &name, SymbolType type, bool declared);
    virtual ~Symbol();

    const string &getName() const;
    void setDeclared(bool declared);
    bool isDeclared() const;

    string toString() const;
    string getType() const;

    llvm::AllocaInst *getAlloc() const;
    void setAlloc(llvm::AllocaInst *alloc);
    Function *getFunc() const;
    void setFunc(Function *func);
};


#endif //LAB02_SYMBOL_H
