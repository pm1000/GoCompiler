//
// Created by philipp on 06.06.21.
//

#include "../../header/Symbol/SymbolTree.h"

SymbolTree::SymbolTree(const string &scopeName) : scopeName(scopeName) {}

SymbolTree::~SymbolTree() {

}

void SymbolTree::putSymbol(string name, Type type, bool declared) {
    auto it = table.find(name);
    if (it != table.end()){


    }
}
