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

                //save func in symbol tree for future function calls
                cout << node->getAssignID()->getValue() << endl;
                Symbol* fSym = symbolTree->getDeclaredSymbol(node->getAssignID()->getValue());
                if (fSym == nullptr) {
                    std::cerr << "Error, unused symbol" << endl;
                    exit(1);
                }
                fSym->setFunc(func);

                //after this scope needs to be opened
                if (children[pos]->getType() == SCOPE) {
                    auto scopeKids = children[pos]->getChildren();
                    int scopePos = 0;
                    //complete function scope gets generated with recursive calls on build scope
                    buildScope(children[pos], scopeKids, &scopePos, nullptr, func, true);
                }
            }
        } else {
            //if it is not a function call the function recusively
            auto children = node->getChildren();
            for (int i = 0; i < children.size(); ++i) {
                astDFS(children[i], children[i]->getSymbolTreeNode());
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
                                   Function* f, bool outRec) {
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
            buildScope(children[*pos], kids, &subPos, nestedBlock, f, false);
        }

        if (children[*pos]->getType() == RCURLY) {
            cout << "Scope closed" << endl;

            if (outRec) {
                llvm::Instruction* ret = llvm::ReturnInst::Create(context, nullptr, current);
            }

            return;
        }

        if (children[*pos]->getType() == EXPRESSION) {
            cout << "Expression" << endl;
            //var id = number --> zuweisung             0
            //id = id + number --> addition + zuweisung 1
            //id = number + id --> addition + zuweisung 2
            //id = number --> zuweisung 3
            //id = id --> zuweisung 4

            auto debug = children[*pos]->getExpressionType();
            switch (children[*pos]->getExpressionType()) {

                //var id = number --> zuweisung
                case 0 : {
                    TreeNode* assignNode = children[*pos]->getAssignID();
                    double value = children[*pos]->getExpNum();
                    SymbolTree* symNode = children[*pos]->getSymbolTreeNode();

                    Value* number = llvm::ConstantFP::get(context, llvm::APFloat(value));

                    Symbol* symbol = symNode->getDeclaredSymbol(assignNode->getValue());
                    auto assignVar = symbol->getAlloc();
                    if (assignVar == nullptr) {
                        // new allocation needed
                        symbol->setAlloc(new llvm::AllocaInst(llvm::Type::getFP128Ty(context), 0,
                                                       assignNode->getValue(), current));
                    }
                    llvm::Instruction* assign = new llvm::StoreInst(number, symbol->getAlloc(), current);


                } break;


                //id1 = id2 + number --> addition + zuweisung
                case 1 : {

                    SymbolTree* symNode = children[*pos]->getSymbolTreeNode();
                    TreeNode* assign = children[*pos]->getAssignID(); //id1
                    pair<TreeNode*, double> p = children[*pos]->getExpID_Num(); //id2, number

                    Value* number1 = llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), p.second);

                    Symbol* id2 = symNode->getDeclaredSymbol(p.first->getValue());
                    if (id2 == nullptr) {
                        std::cerr << "Error, use of undeclared Symbol" << endl;
                        exit(1);
                    }

                    llvm::BinaryOperator* add = llvm::BinaryOperator::Create(Instruction::Add, id2->getAlloc(), number1, "AddInstruction");
                    current->getInstList().push_back(add);

                    Symbol* id1 = symNode->getDeclaredSymbol(assign->getValue());
                    if (id1 == nullptr) {
                        std::cerr << "Error, use of undeclared Symbol" << endl;
                        exit(1);
                    }

                    llvm::Instruction* store = new llvm::StoreInst(add,id1->getAlloc(),current);

                } break;


                //id = number + id --> addition + zuweisung
                case 2 : {
                    SymbolTree* symNode = children[*pos]->getSymbolTreeNode();
                    TreeNode* assign = children[*pos]->getAssignID(); //id1
                    pair<double, TreeNode*> p = children[*pos]->getExpNum_ID(); //id2, number

                    Value* number1 = llvm::ConstantFP::get(llvm::Type::getDoubleTy(context), p.first);

                    Symbol* id2 = symNode->getDeclaredSymbol(p.second->getValue());
                    if (id2 == nullptr) {
                        std::cerr << "Error, use of undeclared Symbol" << endl;
                        exit(1);
                    }

                    llvm::BinaryOperator* add = llvm::BinaryOperator::Create(Instruction::Add, id2->getAlloc(), number1, "AddInstruction");
                    current->getInstList().push_back(add);

                    Symbol* id1 = symNode->getDeclaredSymbol(assign->getValue());
                    if (id1 == nullptr) {
                        std::cerr << "Error, use of undeclared Symbol" << endl;
                        exit(1);
                    }

                    llvm::Instruction* store = new llvm::StoreInst(add,id1->getAlloc(),current);
                } break;

                //id = number --> zuweisung
                case 3 : {
                    TreeNode* assignNode = children[*pos]->getAssignID();
                    double value = children[*pos]->getExpNum();
                    SymbolTree* symNode = children[*pos]->getSymbolTreeNode();

                    Value* number = llvm::ConstantFP::get(context, llvm::APFloat(value));

                    Symbol* symbol = symNode->getDeclaredSymbol(assignNode->getValue());
                    if (symbol == nullptr) {
                        std::cerr << "Error, use of undeclared symbol" << endl;
                        exit(1);
                    }

                    llvm::Instruction* assign = new llvm::StoreInst(number, symbol->getAlloc(), current);

                } break;

                //id = id --> zuweisung
                case 4 : {
                    TreeNode* assignNode = children[*pos]->getAssignID();
                    TreeNode* assignValue = children[*pos]->getExpID();
                    SymbolTree* symNode = children[*pos]->getSymbolTreeNode();

                    Symbol* assignSym = symNode->getDeclaredSymbol(assignNode->getValue());
                    Symbol* assignedVal = symNode->getDeclaredSymbol(assignValue->getValue());
                    if (assignSym == nullptr || assignedVal == nullptr) {
                        std::cerr << "Error, use of undeclared symbol" << endl;
                        exit(1);
                    }

                    llvm::Instruction* assign = new llvm::StoreInst(assignedVal->getAlloc(), assignSym->getAlloc(), current);

                } break;

                case 5 : {
                    //todo function call

                    TreeNode* funcID = children[*pos]->getExpFuncID();
                    SymbolTree* symNode = children[*pos]->getSymbolTreeNode();

                    Symbol* func = symNode->getDeclaredSymbol(funcID->getValue());
                    if (func == nullptr) {
                        std::cerr << "Error, use of undeclared symbol" << endl;
                        exit(1);
                    }

                    std::vector<Value*> emptyArgs;
                    llvm::Instruction* fCall = llvm::CallInst::Create(func->getFunc(), emptyArgs, "call", current);

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
