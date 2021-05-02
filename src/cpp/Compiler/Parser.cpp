//
// Created by philipp on 02.05.21.
//

#include <stdexcept>
#include "../../header/Compiler/Parser.h"

Parser::Parser(std::string content){
    this->content = content;
}

Parser::~Parser() = default;

void Parser::parse() {

    // Parse the string, fill the ast-tree and the symbol table
    char c = getNextChar();

    //check for <PACKAGE_INCLUDE> (see docs/grammar.txt)
    std::string current = "";
    while (c != 0){
        //check for <PACKAGE_INCLUDE>
        checkForStart();
        checkFunc();
    }

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

bool Parser::isWS(char c) {
    if ('\t' == c || '\n' == c || ' ' == c)
        return true;
    return false;
}

bool Parser::isLetter(char c) {
    if ((c >= 'a' && c <= 'z') || (c <= 'A' && c <= 'Z'))
        return true;
    return false;
}

bool Parser::isDigit(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

//check for <PACKAGE_INCLUDE>  : { <ws>* <package> <ws>+ <id> <ws>+ } (see docs/grammar.txt)
bool Parser::checkForStart() {
    char c = getNextChar();
    std::string current = "";

    while (c != 0) {
        //checks for ws before keyword
        while (isWS(c))
            c = getNextChar();

        //finds 'package keyword
        while (!isWS(c)) {
            current += c;
            c = getNextChar();
        }

        if (current != "package")
            throw std::invalid_argument("Expected keyword <package> but found" + current);

        while (isWS(c))
            c = getNextChar();

        current = "";
        while (!isWS(c)) {
            current += c;
            c = getNextChar();
        }

        if (!checkID(current))
            throw std::invalid_argument("Expected token for <package> but found" + current);
    }
}

//checks for id = [_a-zA-Z][a-zA-Z0-9_]* (see docs/grammar.txt)
bool Parser::checkID(std::string id) {
    if (id.length() > 0){
        //first char needs to be a letter
        if (!isLetter(id[0]))
            return false;

        //check for invalid chars
        for (int i = 1; i < id.length(); ++i){
            if (!isLetter(id[i]) || !isDigit(id[i]) || id[i] != '_')
                return false;
        }

        return true;
    }else
        return false;
}

//checks for <FUNCTION> : { <ws>* <func> <ws>+ <id> <ws>* <(> <ws>* <)> <ws>* <SCOPE> <ws>* } (see docs/grammar.txt)
void Parser::checkFunc() {

    char c = getNextChar();
    std::string current;

    //removes ws
    while (isWS(c))
        c = getNextChar();

    //checks for "func"
    while (!isWS(c)){
        current += getNextChar();
        c = getNextChar();
    }

    if (current != "func")
        throw std::invalid_argument("Expected <func> keyword but found " + current);

    //removes ws
    while (isWS(c))
        c = getNextChar();

    //checks for token
    current = "";
    while(isIDCharacter(c)){
        current += c;
        c = getNextChar();
    }
    if (!checkID(current))
        throw std::invalid_argument("Expected token but found " + current);

    while(isWS(c))
        c = getNextChar();

    //checks for <(>
    if (c != '(') {
        current += c;
        throw std::invalid_argument("Expected <(> but found " + current);
    }

    //removes ws
    c = getNextChar();
    while (isWS(c))
        c = getNextChar();

    //checks for <)>
    if (c!= ')'){
        current += c;
        throw std::invalid_argument("Expected <)> but found " + current);
    }

    //removes ws
    c = getNextChar();
    while (isWS(c))
        c = getNextChar();

    checkScope();
}

bool Parser::checkScopeBegin(char c) {
    if (c == '{')
        return true;
    return false;
}

bool Parser::checkScopeEnd(char c) {
    if (c == '}')
        return true;
    return false;
}

bool Parser::isIDCharacter(char c) {
    if (isLetter(c) || isDigit(c) || c == '_')
        return true;
    return false;
}

//checks for <SCOPE> : { <ws>* <{> <ws>* <EXPRESSION>* <ws>* <}> <ws>* } (see docs/grammar.txt)
void Parser::checkScope() {
    char c = getNextCharNoWS();

    if (!checkScopeBegin(c))
        throw std::invalid_argument("Expected new scope");

    while (!checkScopeEnd(c)){
        if (c == 0)
            throw std::invalid_argument("EOF before a scope was closed");
        checkExpression();
    }
}

char Parser::getNextCharNoWS() {
    char c = getNextChar();
    while (isWS(c))
        c = getNextChar();
    return c;
}

void Parser::checkExpression() {
    char c = getNextCharNoWS();
    std::string current = "";

    //checks for <var>
    while (!isWS(c)){
        current += c;
        c = getNextChar();
    }

    if (current != "var")
        throw std::invalid_argument("Expected <var> keyword but found: " + current);

    c = getNextCharNoWS();

    current = "";
    //checks for <id>
    while(!isWS(c) && isIDCharacter(c)){
        current += c;
        c = getNextChar();
    }

    if (!checkID(current))
        throw std::invalid_argument("Expected token but found: " + current);

    c = getNextCharNoWS();

    //checks for <=>
    if (c != '='){
        current += c;
        throw std::invalid_argument("Expected <=> but found: " + current);
    }

    if (!isNumber())
        throw std::invalid_argument("Expected a number but sadly there was no number:(");
    }

bool Parser::isNumber() {
    return false;
}
