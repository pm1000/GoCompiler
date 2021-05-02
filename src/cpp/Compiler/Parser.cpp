//
// Created by philipp on 02.05.21.
//

#include "../../header/Compiler/Parser.h"

Parser::Parser() = default;

Parser::~Parser() = default;

void Parser::parse(std::string content) {

    // Parse the string, fill the ast-tree and the symbol table

}

Tree *Parser::getAstRoot() {
    return this->astRoot;
}

Tree *Parser::getSymbolTableRoot() {
    return this->symbolTableRoot;
}
