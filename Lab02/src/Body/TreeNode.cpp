//
// Created by yabr on 16.05.21.
//

#include "../Header/TreeNode.h"

TreeNode *createTreeNode(tokenType type, string value) {

    TreeNode* tmp = new TreeNode;
    tmp->value = value;
    tmp->type = type;

    return tmp;
}