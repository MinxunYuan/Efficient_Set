#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>

TreeNode* newNode(int item);

TreeNode* treeInsert(TreeNode* root, int item, bool* flg);

TreeNode* leftRotate(TreeNode*);

TreeNode* rightRotate(TreeNode*);

#endif
