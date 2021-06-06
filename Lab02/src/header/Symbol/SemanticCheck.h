//
// Created by philipp on 06.06.21.
//

#ifndef LAB02_SEMANTICCHECK_H
#define LAB02_SEMANTICCHECK_H


#include "../TreeNode.h"
#include "SymbolTree.h"

class SemanticCheck {
private:
    TreeNode* ast;
    SymbolTree* symbolTree;

    vector<string> scopeDfs(SymbolTree* symTree);
    void createScopeStructure(SymbolTree* sym, TreeNode* node);

public:
    SemanticCheck(TreeNode *ast);
    virtual ~SemanticCheck();

    SymbolTree* checkTree();
};


#endif //LAB02_SEMANTICCHECK_H
