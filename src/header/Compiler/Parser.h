//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_PARSER_H
#define Y_RASTER_A_PARSER_H


#include "../Tree/Tree.h"
#include "../Tree/BranchTree.h"

class Parser {
private:
    Tree* astRoot = new BranchTree(nullptr, "");
    Tree* symbolTableRoot = new BranchTree(nullptr, "");
    std::string content;
    char getNextChar();
    static bool isWS(char c) ;
    static bool isLetter(char c) ;
    static bool isNumber(char c) ;
    bool checkForStart();
    bool checkID(std::string id);
    bool checkFunc();
    bool checkIDCharacter(char c);
    bool checkScopeBegin(char c);
    bool checkScopeEnd(char c);
    bool checkScope();
public:
    Parser(std::string content);
    virtual ~Parser();

    void parse();

    Tree* getAstRoot();
    Tree* getSymbolTableRoot();
};


#endif //Y_RASTER_A_PARSER_H
