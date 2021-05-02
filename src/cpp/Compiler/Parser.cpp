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
    return 0;
}

bool Parser::isWS(char c) const {
    if ('\t' == c || '\n' == c || ' ' == c)
        return true;
    return false;
}

bool Parser::isLetter(char c) const {
    if ((c >= 'a' && c <= 'z') || (c <= 'A' && c <= 'Z'))
        return true;
    return false;
}

bool Parser::isNumber(char c) const {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
