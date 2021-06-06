//
// Created by philipp on 06.06.21.
//

#ifndef LAB02_SYMBOL_H
#define LAB02_SYMBOL_H

#include "string"

using std::string;

enum Type {START, FUNCTION, VARIABLE};

class Symbol {
private:
    string name;
    Type type;
    bool declared;

public:
    Symbol(const string &name, Type type, bool declared);
    virtual ~Symbol();

    void setDeclared(bool declared);
    bool isDeclared() const;
};


#endif //LAB02_SYMBOL_H
