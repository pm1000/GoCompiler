//
// Created by philipp on 06.06.21.
//

#include "../../header/Symbol/Symbol.h"

Symbol::Symbol(const string &name, SymbolType type, bool declared) {
        this->name = name;
        this->type = type;
        this->declared = declared;
        this->alloc = nullptr;
}

Symbol::~Symbol() {

}

void Symbol::setDeclared(bool declared) {
    Symbol::declared = declared;
}

bool Symbol::isDeclared() const {
    return declared;
}

const string &Symbol::getName() const {
    return name;
}

string Symbol::toString() const {
    string tmp = this->name + " from type " + this->getType() + ". ";
    tmp += (this->declared) ? "Declared here." : "Not declared here.";
    return tmp;
}

string Symbol::getType() const {
    switch (this->type) {
        case SYM_FUNCTION:
            return "function";
        case SYM_START:
            return "start";
        case SYM_VARIABLE:
            return "variable";
        default:
            return "ERROR! Type not defined.";
    }
}

Value *Symbol::getValue() const {
    return val;
}

void Symbol::getVal(double value, LLVMContext context) {
    this->val = llvm::ConstantFP::get(context, llvm::APFloat(value));
}

void Symbol::setVal(Value *value) {
    this->val = value;
}

llvm::AllocaInst *Symbol::getAlloc() const {
    return alloc;
}

void Symbol::setAlloc(llvm::AllocaInst *alloc) {
    Symbol::alloc = alloc;
}
