#ifndef AVL_TREE_H
#define AVL_TREE_H

TreeNode* newNode(int item);

TreeNode* treeInsert(TreeNode* root, int item);

TreeNode* leftRotate(TreeNode*);

TreeNode* rightRotate(TreeNode*);

#endif
