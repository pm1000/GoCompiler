//
// Created by philipp on 02.05.21.
//

#include "../header/CompileController.h"



/**
 *
 */
CompileController::CompileController() = default;



/**
 *
 */
CompileController::~CompileController() = default;



/**
 *
 */
void CompileController::init(std::string filePath) {
    this->filePath = filePath;
}



/**
 *
 */
void CompileController::start() {

    // ################################################################################
    // Start Phase 1+2: Parser+Syntax
    driver drv;

    drv.file = this->filePath;

    // Change logging
    drv.trace_parsing = this->logging;
    drv.trace_scanning = this->logging;

    drv.parse(drv.file);
    this->astRoot = drv.root;


    // ################################################################################
    // Start Phase 3: Semantic
    SemanticCheck* semanticCheck = new SemanticCheck(this->astRoot);
    try {
        semanticCheck->checkTree();
        this->symbolTable = semanticCheck->getSymbolTree();

        //code generation
        LLVMContext context;
        module = new Module(this->filePath, context);
        astDFS(this->astRoot, this->symbolTable);
        module->print(llvm::errs(), nullptr);

    } catch (std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    delete semanticCheck;
}



/**
 *
 */
TreeNode *CompileController::getAstRoot() {
    return this->astRoot;
}



/**
 *
 */
SymbolTree *CompileController::getSymbolTableRoot() {
    return this->symbolTable;
}



/**
 *
 */
void CompileController::setLogging(bool value) {
    this->logging = value;
}

//searches the whole ast tree and calls sub functions to generate code
void CompileController::astDFS(TreeNode *node, SymbolTree* symbolTree) {

    //function gets called recursively --> check for nullptr
    if (node != nullptr) {

        //if node is function
        if (node->getType() == FUNCTION) {
            auto children = node->getChildren();
            if (children.size() == 0) {
                //error if function node has no children
                std::cerr <<"Expected a function" << endl;
                node = nullptr;
            } else {
                //build function def
                int pos = 0;
                Function* func = buildFunc(node, children, &pos); // automatically inserted in the function by using the module operator
                //after this scope needs to be opened
                if (children[pos]->getType() == SCOPE) {
                    auto scopeKids = children[pos]->getChildren();
                    int scopePos = 0;
                    //complete function scope gets generated with recursive calls on build scope
                    buildScope(children[pos], scopeKids, &scopePos, nullptr, func);
                }
            }
        } else {
            //if it is not a function call the function recusively
            auto children = node->getChildren();
            for (int i = 0; i < children.size(); ++i) {
                astDFS(children[i], symbolTree);
            }
        }
    }
}

// creates a function
Function* CompileController::buildFunc(TreeNode* parent, vector<TreeNode *> children, int *pos) {
    llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context),false);
    string id = parent->getFunctionID();
    while (*pos < children.size() && children[*pos]->getType() != SCOPE) {
        *pos = *pos + 1;
    }
    cout << "Found func" << endl;
    return llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, id, module);
}

//creates a scope
void CompileController::buildScope(TreeNode *parent, vector<TreeNode *> children, int *pos, BasicBlock *current,
                                   Function* f) {
    while (*pos < children.size()) {

        if (children[*pos]->getType() == LCURLY) {
            if (current == nullptr) {
                //standart block
                current = BasicBlock::Create(context, "Scope",f);
                cout << "Scope opened" << endl;
            } else {
                //nested blocks
                cout << "Scope opened" << endl;
            }
        }

        if (children[*pos]->getType() == SCOPE) {
            //nested block gets opened
            auto kids = children[*pos]->getChildren();
            int subPos = 0;
            BasicBlock* nestedBlock = BasicBlock::Create(context,"Scope",f, current);
            buildScope(children[*pos], kids, &subPos, nestedBlock, f);
        }

        if (children[*pos]->getType() == RCURLY) {
            cout << "Scope closed" << endl;
            return;
        }

        if (children[*pos]->getType() == EXPRESSION) {
            cout << "Expression" << endl;
            //var id = number --> zuweisung             0
            //id = id + number --> addition + zuweisung 1
            //id = number + id --> addition + zuweisung 2
            //id = number --> zuweisung 3
            //id = id --> zuweisung 4

            switch (children[*pos]->getExpressionType()) {

                //var id = number --> zuweisung
                case 0 : {
                    TreeNode* assignNode = children[*pos]->getAssignID();
                    double value = children[*pos]->getExpNum();

                    Value* id = assignNode->getSymbolTreeNode()->getDeclaredSymbol(assignNode->getValue())->getValue();
                    Value* number = llvm::ConstantFP::get(context, llvm::APFloat(value));

                    //llvm::Instruction* allocate = new llvm::AllocaInst(...); // TODO
                    llvm::Instruction* assign = new llvm::StoreInst(number, id, current);

                } break;

                //id1 = id2 + number --> addition + zuweisung
                case 1 : {

                    TreeNode* assign = children[*pos]->getAssignID(); //id1
                    pair<TreeNode*, double> p = children[*pos]->getExpID_Num(); //id2, number

                    Value* id2 = p.first->getSymbolTreeNode()->getDeclaredSymbol(p.first->getValue())->getValue();
                    Value* number1 = llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), p.second);

                    llvm::BinaryOperator* add = llvm::BinaryOperator::Create(Instruction::Add, id2, number1, "AddInstruction");
                    current->getInstList().push_back(add);


                    //p.first->getSymbolTreeNode()->getDeclaredSymbol(p.first->getValue())->setVal();

                } break;

                //id = number + id --> addition + zuweisung
                case 2 : {

                } break;

                //id = number --> zuweisung
                case 3 : {



                } break;

                //id = id --> zuweisung
                case 4 : {

                } break;
                default: {
                    std::cerr << "Wenn du das hier siehst, ist etwas grundlegend falsch gelaufen. Denke bitte nochmal drüber"
                            " nach, ob Informatik das richtige für dich ist!"<< endl;
                    exit(1);
                }
            }
        }

        *pos = *pos + 1;
    }
}

