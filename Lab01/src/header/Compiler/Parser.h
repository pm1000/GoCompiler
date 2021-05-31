//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_PARSER_H
#define Y_RASTER_A_PARSER_H

#include <stdexcept>

#include "../Tree/Tree.h"
#include "../Tree/BranchTree.h"
#include "../Tree/TokenTree.h"
#include "../Tree/ScopeTree.h"

class Parser {
private:
    Tree* astRoot = new BranchTree(nullptr, "Root");
    Tree* symbolTableRoot = new ScopeTree(nullptr, "Root");
    std::string content;
    char currentChar;
    int pos;
    int line;
    Tree* currentBranch;
    Tree* currentScope;

    char getNextChar();
    static bool isWS(char c) ;
    static bool isLetter(char c) ;
    static bool isDigit(char c) ;
    bool checkForStart();
    bool checkID(std::string id);
    void checkFunc();
    bool isIDCharacter(char c);
    bool checkScopeBegin(char c);
    bool checkScopeEnd(char c);
    void checkScope();
    char getNextCharNoWS();
    void checkExpression();
    bool isNumber();

public:
    Parser(std::string content);
    virtual ~Parser();

    void parse();
    Tree* getAstRoot();
    Tree* getSymbolTableRoot();
    int getLine() const;
};


#endif //Y_RASTER_A_PARSER_H
