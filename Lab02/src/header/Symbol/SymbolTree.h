//
// Created by philipp on 06.06.21.
//

#ifndef LAB02_SYMBOLTREE_H
#define LAB02_SYMBOLTREE_H

#include "Symbol.h"
#include "unordered_map"
#include "string"

using std::string;
using std::unordered_map;

class SymbolTree {
private:
    string scopeName;
    unordered_map<string,Symbol*> table;

public:
    SymbolTree(const string &scopeName);
    virtual ~SymbolTree();

    void putSymbol(string name, Type type, bool declared);


};


#endif //LAB02_SYMBOLTREE_H
