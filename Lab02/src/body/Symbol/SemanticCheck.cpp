//
// Created by philipp on 06.06.21.
//

#include "../../header/Symbol/SemanticCheck.h"

SemanticCheck::SemanticCheck(TreeNode *ast) : ast(ast) {
    this->symbolTree = new SymbolTree("SYM_START");
}

SemanticCheck::~SemanticCheck() {

}

SymbolTree* SemanticCheck::checkTree() {
    SymbolTree* funcNode = new SymbolTree("Functions");
    SymbolTree* scopes = new SymbolTree("scopes");
    symbolTree->addChild(funcNode);
    symbolTree->addChild(scopes);
    dFsFunc(ast, funcNode);
    createScopeStructure(scopes,ast);
    vector<string> undecSym = scopeDfs(scopes);

    if (undecSym.size() != 0){
        string out;
        for (const auto& symbol : undecSym) {
            out += symbol + ", ";
        }
        throw new std::runtime_error("Undeclared Symbols: " + out + " FIX IT!");
    }
}

SymbolTree* SemanticCheck::dFsFunc(TreeNode* root, SymbolTree* funcNode) {
    if (root){
        //important nodes: scope and function
        if (root->getType() == FUNCTION){
            functionCheck(root,funcNode);
        }
        vector<TreeNode*> kids = root->getChildren();
        for (int i = 0; i < kids.size(); ++i){
            dFsFunc(kids[i], funcNode);
        }
    }
}

vector<string> SemanticCheck::scopeDfs(SymbolTree* node) {
    vector<string> ret;
    if (node != nullptr){
        vector<SymbolTree*> kids = node->getChildren();

        for (int i = 0; i < kids.size(); ++i){
            vector<string> tmp = scopeDfs(kids[i]);
            ret.insert(ret.end(), tmp.begin(), tmp.end());
        }

        int i = 0;
        while (i < ret.size()) {
            if (node->containsDeclared(ret[i])) {
                ret.erase(ret.begin() + i);
            } else
                ++i;
        }

        vector<string> tmp = node->getAllUndelaredSymbol();
        ret.insert(ret.end(),tmp.begin(), tmp.end());
    }
    return ret;
}

void SemanticCheck::functionCheck(TreeNode *node, SymbolTree *symTree) {
    if (node){
        vector<TreeNode*> kids = node->getChildren();
        for (int i = 0; i < kids.size(); ++i){
            if (kids[i]->getType() == ID){
                symTree->putSymbol(kids[i]->getValue(), SYM_FUNCTION, true);
            }
        }
    }
}

void SemanticCheck::createScopeStructure(SymbolTree *sym, TreeNode *node) {
    if (node != nullptr){
        if (node->getType() == SCOPE){
            SymbolTree* subScope = new SymbolTree(node->getTypeName());
            sym->addChild(subScope);
            vector<TreeNode*> kids = node->getChildren();
            for (int i = 0; i < kids.size(); ++i){
                createScopeStructure(subScope, kids[i]);
            }
        }
        else{
            string id;
            bool declared = false;
            if (node->getType() == EXPRESSION) {
                id = node->getExpressionID();
                declared = node->findChildType(VAR);
                sym->putSymbol(id, SYM_VARIABLE, declared);
            } else {
                vector<TreeNode *> kids = node->getChildren();
                for (int i = 0; i < kids.size(); ++i) {
                    createScopeStructure(sym, kids[i]);
                }
            }
        }
    }
}
