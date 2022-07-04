#include "SetStructs.h"
#include "AVLTree.h"
#include "Set.h"
#include <stdlib.h>
#include <stdio.h>

static int max(int a, int b) {
    return a > b ? a : b;
}

static int getHeight(TreeNode* node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

static int getBalance(TreeNode* node) {
    if (!node->left && !node->right)
        return 1;
    else if (!node->left) return -node->right->height;
    else if (!node->right) return node->left->height;
    return node->left->height - node->right->height;
}

// typedef struct set *Set;
TreeNode* newNode(int item) {
    TreeNode* node = malloc(sizeof(TreeNode));
    (*node) = (TreeNode){
        .item = item,
        .left = NULL,
        .right = NULL,
        .height = 1,
    };
    return node;
}

TreeNode* treeInsert(TreeNode* root, int item) {
    if (!root) return newNode(item);
    // 因为这里new完node直接就return了，不会进下面的height赋值环节
    // 所以node->height初始化要赋值为1

    if (item < root->item) {
        root->left = treeInsert(root->left, item);
    } else if (item > root->item) {
        root->right = treeInsert(root->right, item);
    }
    // insert完之后，从后往前算一下途径node的平衡因子
    // 拿balance之前，一定得判断左右子树是否为NULL
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // printf("%d ,height:%d\n", root->item, root->height);
    int balance = getBalance(root);

    // printf("%d %d\n", root->item, balance);
    if (balance > 1) {
        //  R
        // printf("rightRotate\n");
        if (item > root->left->item) {
            // RL
            root->left = leftRotate(root->left);
        }
        root = rightRotate(root);
    } else if (balance < -1) {
        // L
        // printf("leftRotate\n");

        if (item < root->right->item) {
            root->right = rightRotate(root->right);
        }
        root = leftRotate(root);
    }
    return root;
}

TreeNode* leftRotate(TreeNode* tree) {

    TreeNode* tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;
    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));

    return tmp;
}

// Move left child to root, rearrange links to reain order
TreeNode* rightRotate(TreeNode* tree) {

    TreeNode* tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;
    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));

    return tmp;
}

