//
// Created by philipp on 06.06.21.
//

#include "../../header/Symbol/SymbolTree.h"

SymbolTree::SymbolTree(const string &scopeName) : scopeName(scopeName) {}

SymbolTree::~SymbolTree() {

}

void SymbolTree::putSymbol(string name, SymbolType type, bool declared) {
    auto it = table.find(name);
    if (it == table.end()){
        table.insert({name, new Symbol(name, type, declared)});
    }
    else{
        // error checking
        if (it->second->isDeclared() && declared){
            // error double declaration
            throw new std::runtime_error("Double declaration of " + name + " please fix this:(. I can’t handle " +
                                                                           "this error for you!");
        }
    }

}

void SymbolTree::addChild(SymbolTree *node) {
    children.push_back(node);
}

vector<string> SymbolTree::getAllUndelaredSymbol() {
    vector<string> undec;

    for (auto it = table.begin(); it != table.end(); ++it){
        if (!it->second->isDeclared())
            undec.push_back(it->second->getName());
    }

    return undec;
}

const vector<SymbolTree *> &SymbolTree::getChildren() const {
    return children;
}

bool SymbolTree::containsDeclared(string name) {
    auto it = table.find(name);
    if (it != table.end()){
        if (it->second->isDeclared())
            return true;
    }
    return false;
}
