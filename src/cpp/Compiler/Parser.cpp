//
// Created by philipp on 02.05.21.
//

#include "../../header/Compiler/Parser.h"

Parser::Parser(std::string content){
    this->content = content;
}

Parser::~Parser() = default;

void Parser::parse() {

    // Parse the string, fill the ast-tree and the symbol table

}

Tree *Parser::getAstRoot() {
    return this->astRoot;
}

Tree *Parser::getSymbolTableRoot() {
    return this->symbolTableRoot;
}

char Parser::getNextChar() {
    static unsigned int pos = 0;
    return (pos < this->content.size()) ? this->content.at(pos++) : 0;
}
