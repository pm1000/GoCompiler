//
// Created by philipp on 02.05.21.
//

#include "../../header/Compiler/Parser.h"

Parser::Parser(std::string content){
    this->content = content;
    this->pos = 0;
    this->line = 1;
}

Parser::~Parser() = default;

void Parser::parse() {

    // Parse the string, fill the ast-tree and the symbol table
    //check for <PACKAGE_INCLUDE> (see docs/grammar.txt)
    std::string current = "";
    this->currentScope = this->symbolTableRoot;
    this->currentBranch = this->astRoot;
    checkForStart();
    this->currentBranch = this->astRoot;
    checkFunc();


}

Tree *Parser::getAstRoot() {
    return this->astRoot;
}

Tree *Parser::getSymbolTableRoot() {
    return this->symbolTableRoot;
}

char Parser::getNextChar() {
    if (pos < this->content.size()) {
        this->currentChar = this->content.at(pos);
        pos++;
    } else {
        currentChar = 0;
    }

    if (currentChar == '\n')
        ++line;

    return this->currentChar;
}

bool Parser::isWS(char c) {
    if ('\t' == c || '\n' == c || ' ' == c)
        return true;
    return false;
}

bool Parser::isLetter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
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

    this->currentBranch= new BranchTree(this->astRoot, "PACKAGE_INCLUDE");
    this->astRoot->addChild(this->currentBranch);

    char c = getNextChar();
    std::string current = "";

        //checks for ws before keyword
        while (isWS(c))
            c = getNextChar();

        //finds 'package keyword
        while (!isWS(c)) {
            current += c;
            c = getNextChar();
        }

        if (current != "package")
            throw std::invalid_argument("Expected keyword <package> but found: " + current);
        Tree* tokenPackage = new TokenTree(this->currentBranch, "package");
        this->currentBranch->addChild(tokenPackage);

        while (isWS(c))
            c = getNextChar();

        current = "";
        while (!isWS(c)) {
            current += c;
            c = getNextChar();
        }

        if (!checkID(current))
            throw std::invalid_argument("Expected token for <package> but found: " + current);

        return true;
}

//checks for id = [_a-zA-Z][a-zA-Z0-9_]* (see docs/grammar.txt)
bool Parser::checkID(std::string id) {
    if (id.length() > 0){
        //first char needs to be a letter
        if (!isLetter(id[0]))
            return false;

        //check for invalid chars
        for (int i = 1; i < id.length(); ++i){
            if (!isLetter(id[i]) && !isDigit(id[i]) && id[i] != '_')
                return false;
        }

        // Add symbol to table
        Tree* newId = new SymbolTree(this->currentScope, id);
        this->currentScope->addChild(newId);

        // Add ast element
        Tree* token_id = new TokenTree(this->currentBranch, "id");
        token_id->addChild(newId);
        this->currentBranch->addChild(token_id);

        return true;
    }else
        return false;
}

//checks for <FUNCTION> : { <ws>* <func> <ws>+ <id> <ws>* <(> <ws>* <)> <ws>* <SCOPE> <ws>* } (see docs/grammar.txt)
void Parser::checkFunc() {

    Tree* currentFunc = new BranchTree(this->currentBranch, "FUNCTION");
    this->currentBranch->addChild(currentFunc);
    this->currentBranch = currentFunc;

    char c = getNextChar();
    std::string current;

    //removes ws
    while (isWS(c))
        c = getNextChar();

    //checks for "func"
    while (!isWS(c)){
        current += c;
        c = getNextChar();
    }

    if (current != "func")
        throw std::invalid_argument("Expected <func> keyword but found " + current);
    Tree* token_func = new TokenTree(currentFunc, "func");
    currentFunc->addChild(token_func);

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
        current = c;
        throw std::invalid_argument("Expected <(> but found " + current);
    }
    Tree* token_bracket_open = new TokenTree(currentFunc, "(");
    currentFunc->addChild(token_bracket_open);

    //removes ws
    c = getNextChar();
    while (isWS(c))
        c = getNextChar();

    //checks for <)>
    if (c!= ')'){
        current = c;
        throw std::invalid_argument("Expected <)> but found " + current);
    }
    Tree* token_bracket_close = new TokenTree(currentFunc, ")");
    currentFunc->addChild(token_bracket_close);

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
    Tree* currentBranch = new BranchTree(this->currentBranch, "SCOPE");
    this->currentBranch->addChild(currentBranch);
    this->currentBranch = currentBranch;

    // Add this to symbol table
    Tree* thisScope = this->currentScope;
    this->currentScope = new ScopeTree(this->currentScope, "SCOPE");
    thisScope->addChild(this->currentScope);


    char c = this->currentChar;

    while (isWS(c)){
        c = getNextChar();
    }

    if (!checkScopeBegin(c))
        throw std::invalid_argument("Expected new scope");
    Tree* token_scope_open = new TokenTree(currentBranch, "{");
    currentBranch->addChild(token_scope_open);

    while (!checkScopeEnd(currentChar)){
        if (currentChar == 0)
            throw std::invalid_argument("EOF before a scope was closed");
        checkExpression();
    }

    Tree* token_scope_close = new TokenTree(currentBranch, "}");
    currentBranch->addChild(token_scope_close);

    // Leaving the scope, reset the symbol table to the last scope
    this->currentScope = thisScope;
}

char Parser::getNextCharNoWS() {
    char c = getNextChar();
    while (isWS(c))
        c = getNextChar();
    return c;
}

void Parser::checkExpression() {
    char c = getNextCharNoWS();
    if(c == '}' || c == 0)
        return;

    Tree* currentExpression = new BranchTree(this->currentBranch, "EXPRESSION");
    this->currentBranch->addChild(currentExpression);
    this->currentBranch = currentExpression;


    std::string current = "";
    //checks for <var>
    while (!isWS(c)){
        current += c;
        c = getNextChar();
    }

    if (current != "var")
        throw std::invalid_argument("Expected <var> keyword but found: " + current);
    Tree* token_var = new TokenTree(currentExpression, "var");
    currentExpression->addChild(token_var);

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
    Tree* token_equals = new TokenTree(currentExpression, "=");
    currentExpression->addChild(token_equals);

    if (!isNumber())
        throw std::invalid_argument("Expected a number but sadly there was no number:(");
    Tree* token_number = new TokenTree(currentExpression, "number");
    currentExpression->addChild(token_number);
    }

bool Parser::isNumber() {

    char c = getNextCharNoWS();

    // Check for + and -
    if (c == '+' || c == '-') {
        c = getNextChar();
    }

    // Check for at least one digit
    if (!isDigit(c)) {
        throw std::invalid_argument("A number must contain a digit in the beginning.");
    }

    while (isDigit(c)) {
        c = getNextChar();
    }

    // If the next char is a point
    if (c == '.') {
        c = getNextChar();

        // Check for digits after the point
        while (isDigit(c)) {
            c = getNextChar();
        }

        // No more digit, number is finished
        if (isWS(c)) {
            return true;
        } else {
            throw std::invalid_argument("A number must end with a digit.");
        }

    }else if (isWS(c))
        return true;
    else {
        throw std::invalid_argument("A number must not contain letters.");
    }
}

int Parser::getLine() const {
    return line;
}
