//
// Created by philipp on 06.06.21.
//

#include "../../header/Symbol/SemanticCheck.h"

SemanticCheck::SemanticCheck(TreeNode *ast) : ast(ast) {
    this->symbolTree = new SymbolTree("SYM_START");
}

SemanticCheck::~SemanticCheck() {

}

void SemanticCheck::checkTree() {
    createScopeStructure(symbolTree,ast);
    vector<string> undecSym = scopeDfs(symbolTree);

    if (undecSym.size() != 0){
        string out;
        for (const auto& symbol : undecSym) {
            out += symbol + ", ";
        }
        throw std::runtime_error("Undeclared Symbols: " + out + " FIX IT!");
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
                bool func = node->findChildType(LPAREN);
                try {
                    if (!func)
                        sym->putSymbol(id, SYM_VARIABLE, declared);
                    else
                        sym->putSymbol(id, SYM_FUNCTION, declared);
                } catch (std::exception& e) {
                    std::cerr << e.what() << endl;
                }

            } else {
                if (node->getType() == FUNCTION){
                    id = node->getFunctionID();
                    try {
                        sym->putSymbol(id, SYM_FUNCTION, true);
                    } catch (std::exception& e) {
                        std::cerr << e.what() << endl;
                    }
                }

                vector<TreeNode *> kids = node->getChildren();
                for (int i = 0; i < kids.size(); ++i) {
                    createScopeStructure(sym, kids[i]);
                }
            }
        }
    }
}

SymbolTree *SemanticCheck::getSymbolTree() const {
    return symbolTree;
}
