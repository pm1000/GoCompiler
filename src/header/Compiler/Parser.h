//
// Created by philipp on 02.05.21.
//

#ifndef Y_RASTER_A_PARSER_H
#define Y_RASTER_A_PARSER_H


#include "../Tree/Tree.h"
#include "../Tree/BranchTree.h"

class Parser {
private:
    Tree* astRoot = new BranchTree(nullptr);
    Tree* symbolTableRoot = new BranchTree(nullptr);
    std::string content;
    char getNextChar();
    bool isWS(char c) const;
    bool isLetter(char c) const;
    bool isNumber(char c) const;
public:
    Parser(std::string content);
    virtual ~Parser();

    void parse();

    Tree* getAstRoot();
    Tree* getSymbolTableRoot();
};


#endif //Y_RASTER_A_PARSER_H
