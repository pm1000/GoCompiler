//
// Created by philipp on 06.06.21.
//

#include "../../header/Symbol/SymbolTree.h"

SymbolTree::SymbolTree(const string &scopeName, SymbolTree *parent) {
    this->scopeName = scopeName;
    this->parent = parent;
}

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
            throw std::runtime_error("Double declaration of " + name + " please fix this:(. I can’t handle " +
                                                                           "this error for you!");
        }
    }

}

void SymbolTree::addChild(SymbolTree *node) {
    children.push_back(node);
}

vector<string> SymbolTree::getAllUndeclaredSymbol() {
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



/**
 *
 */
const string &SymbolTree::getScopeName() const {
    return scopeName;
}



/**
 *
 */
vector<string> SymbolTree::getTableEntries() const {

    vector<string> rows;
    for (const auto& symbol : this->table) {
        rows.push_back(symbol.second->toString());
    }
    return rows;
}

Symbol *SymbolTree::getDeclaredSymbol(string sym) {

    //find symbol in table
    auto it = table.find(sym);

    //check if it is available
    if (it != table.end()) {
        //check if it is declared (if yes then return the symbol)
        if (it->second->isDeclared())
            return it->second;
    }

    //recursive call to this function with parent node
    if (parent != nullptr) {
        return parent->getDeclaredSymbol(sym);
    } else {
        //symbol not in this symbol table
        return nullptr;
    }
}