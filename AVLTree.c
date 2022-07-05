#include "SetStructs.h"
#include "AVLTree.h"
#include "Set.h"
#include <stdbool.h>
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

/**
 * @brief
 * get the balance factor of the given node
 * @param node the given node
 * @return node's balance factor
 */
static int getBalance(TreeNode* node) {
    // leaf's balance factor is 0
    if (!node->left && !node->right)
        return 0;
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

/**
 * @brief 
 * insert an item to an AVL tree.
 * If tree's left subtree too deep, rightRotate(tree).
 * If tree's right subtree too deep, leftRotate(tree).
 * Maintaining height of every node
 * 
 * @param root pointer refers to the given AVL tree
 * @param item item that's gonna be inserted
 * @param flg whether item is inserted successfully
 * @return pointer refers to the updated AVL tree
 */
TreeNode* treeInsert(TreeNode* root, int item, bool* flg) {
    if (!root) {
        *flg = true;
        return newNode(item);
    }
    // 因为这里new完node直接就return了，不会进下面的height赋值环节
    // 所以node->height初始化要赋值为1

    if (item < root->item) {
        root->left = treeInsert(root->left, item, flg);
    } else if (item > root->item) {
        root->right = treeInsert(root->right, item, flg);
    }
    // insertion at leaves may cause imbalance
    // insert完之后，从后往前算一下途径node的平衡因子
    // 拿balance之前，一定得判断左右子树是否为NULL
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // printf("%d ,height:%d\n", root->item, root->height);
    int balance = getBalance(root);

    // printf("%d %d\n", root->item, balance);
    // A tree is unbalanced when abs(height(left)-height(right)) > 1
    // If abs(balance) > 1 after updating, rebalance via rotation
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
            // LR
            root->right = rightRotate(root->right);
        }
        root = leftRotate(root);
    }
    return root;
}

/**
 * @brief
 * Rotate tree's right child to root, rearrange links to reain order
 * @param tree the root of this tree gonna be demoted
 * @return the right subtree of this tree
 */
TreeNode* leftRotate(TreeNode* tree) {
    if (tree == NULL) return NULL;
    // tmp refers to tree's right subtree
    TreeNode* tmp = tree->right;
    if (tmp == NULL) return tree;
    tree->right = tmp->left;
    tmp->left = tree;

    // correct height
    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));

    return tmp;
}

/**
 * @brief
 * Rotate tree's left child to root, rearrange links to reain order
 * @param tree the root of this tree gonna be demoted
 * @return the left subtree of this tree
 */
TreeNode* rightRotate(TreeNode* tree) {
    if (tree == NULL) return NULL;
    // temp refers to the tree's left subtree
    TreeNode* tmp = tree->left;
    if (tmp == NULL) return tree;

    tree->left = tmp->right;
    tmp->right = tree;
    // correct height
    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));

    return tmp;
}

