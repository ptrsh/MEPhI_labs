#include "stdlib.h"
#include "tree.h"

void treeInsertLeft(tree_t *tree, tree_t *node) {
    if (tree->left != NULL) {
        treeInsert(tree->left, node);
    } else {
        node->parent = tree;
        tree->left = node;
    }
}

void treeInsertRight(tree_t *tree, tree_t *node) {
    if (tree->right != NULL) {
        treeInsert(tree->right, node);
    } else {
        node->parent = tree;
        tree->right = node;
    }
}

tree_t *treeInit(int key, int value) {
    tree_t *tree = malloc(sizeof(tree_t));
    tree->key = key;
    tree->value = value;
    tree->version = 0;
    tree->left = NULL;
    tree->right = NULL;
    tree->parent = NULL;
    return tree;
}

tree_t *treeSelect(tree_t *tree, int key) {
    if (tree == NULL) return NULL;
    if (tree->key == key) return tree;
    tree_t *res;
    if ((res = treeSelect(tree->right, key)) != NULL)
        return res;
    if ((res = treeSelect(tree->left, key)) != NULL)
        return res;
    return NULL;
}

tree_t *treeSelectMin(tree_t *tree) {
    if (tree->left == NULL)
        return tree;
    return treeSelectMin(tree->left);
}

int treeIsDuplicated(tree_t *tree) {
    return tree != NULL && tree->left != NULL && tree->key == tree->left->key;
}

void treeInsert(tree_t *tree, tree_t *node) {
    if (node->key < tree->key) {
        treeInsertLeft(tree, node);
    } else if (node->key > tree->key) {
        treeInsertRight(tree, node);
    } else if (treeIsDuplicated(tree)) {
        treeInsert(tree->left, node);
    } else {
        node->left = tree->left;
        node->parent = tree;
        node->version = tree->version + 1;
        tree->left = node;
    }
}

void treeDrop(tree_t *tree) {
    if (treeIsDuplicated(tree)) {
        tree_t *tmp = tree->left;
        while (tmp != NULL && tmp->key == tmp->parent->left->key) {
            tmp->version--;
            tmp = tmp->left;
        }
    }
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->parent->left == tree) {
            tree->parent->left = NULL;
        } else {
            tree->parent->right = NULL;
        }
        return;
    }
    if (tree->left != NULL && tree->right != NULL) {
        tree_t *leftmost = treeSelectMin(tree->right);
        tree->key = leftmost->key;
        tree->value = leftmost->value;
        treeDrop(leftmost);
    }
    tree_t *child = tree->left ? tree->left : tree->right;
    if (tree->parent == NULL) {
        tree->key = child->key;
        tree->value = child->value;
        tree->left = child->left;
        tree->right = child->right;
        child->left->parent = tree;
        child->right->parent = tree;
        free(child);
    } else {
        if (tree->parent->left == tree) {
            tree->parent->left = child;
        } else {
            tree->parent->right = child;
        }
    }
}

void treeFree(tree_t *tree) {
    if (tree->right != NULL)
        treeFree(tree->right);
    if (tree->left != NULL)
        treeFree(tree->left);
    free(tree);
}
