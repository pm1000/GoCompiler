//
// Created by philipp on 06.06.21.
//

#ifndef LAB02_SYMBOL_H
#define LAB02_SYMBOL_H

#include "string"

using std::string;

enum SymbolType {SYM_START, SYM_FUNCTION, SYM_VARIABLE};

class Symbol {
private:
    string name;
    SymbolType type;
    bool declared;

public:
    Symbol(const string &name, SymbolType type, bool declared);
    virtual ~Symbol();

    const string &getName() const;
    void setDeclared(bool declared);
    bool isDeclared() const;

    string toString() const;
    string getType() const;
};


#endif //LAB02_SYMBOL_H
