//
// Created by philipp on 06.06.21.
//

#ifndef LAB02_SYMBOLTREE_H
#define LAB02_SYMBOLTREE_H

#include "Symbol.h"
#include "unordered_map"
#include "string"
#include "vector"
#include "exception"

using std::string;
using std::unordered_map;
using std::vector;

class SymbolTree {
private:
    string scopeName;
    unordered_map<string,Symbol*> table;
    vector<SymbolTree*> children;

public:
    SymbolTree(const string &scopeName);
    virtual ~SymbolTree();

    void putSymbol(string name, SymbolType type, bool declared);
    void addChild(SymbolTree* node);
    bool containsDeclared(string name);

    vector<string> getAllUndelaredSymbol();
    const vector<SymbolTree *> &getChildren() const;
};


#endif //LAB02_SYMBOLTREE_H
