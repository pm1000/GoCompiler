//
// Created by philipp on 06.06.21.
//

#include "../../header/Symbol/Symbol.h"

Symbol::Symbol(const string &name, Type type, bool declared) : name(name), type(type), declared(declared) {}

Symbol::~Symbol() {

}

void Symbol::setDeclared(bool declared) {
    Symbol::declared = declared;
}

bool Symbol::isDeclared() const {
    return declared;
}
