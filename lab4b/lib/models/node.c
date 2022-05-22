#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

#define max(x, y) (x > y ? x : y)
#define abs(x) (((x)<0)?-(x):(x))

node_t *create_node(int key, char *info) {
    node_t *node = malloc(sizeof(node_t));
    node->info = info;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
}

int get_height(node_t *node) {
    if (!node)
        return 0;
    return 1 + max(get_height(node->left), get_height(node->right));
}

int get_balance(node_t *node) {
    if (!node)
        return 0;
    return get_height(node->right) - get_height(node->left);
}

node_t *right_rotate(node_t *node) {
    node_t *current = node->left;
    node->left = current->right;
    current->right = node;
    return current;
}

node_t *left_rotate(node_t *node) {
    node_t *current = node->right;
    node->right = current->left;
    current->left = node;
    return current;
}

node_t *balance_node(node_t *node) {
    int node_balance = get_balance(node);
    if (node_balance == 2) {
        if (get_balance(node->right) < 0)
            node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    else if (node_balance == -2) {
        if (get_balance(node->left) > 0)
            node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    return node;
}

node_t *insert_node(node_t *parent, node_t *child) {
    if (!parent)
        return child;

    if (parent->key == child->key) 
        return parent;
    
    else if (parent->key > child->key)
        parent->left = insert_node(parent->left, child);
    else
        parent->right = insert_node(parent->right, child);

    return balance_node(parent);   
}

node_t *delete_min(node_t *node) {
    if (!node->left)
        return node->right;
    node->left = delete_min(node->left);
    return balance_node(node);
}

node_t *delete(node_t *node, int key) {
    if (!node)
        return 0;

    if (node->key == key) {
        node_t *l = node->left;
        node_t *r = node->right;
        free(node->info);
        free(node);
        if (!r) 
            return l;
        node_t *temp = r;
        while (temp->left)
            temp = temp->left;

        temp->left = l;
        temp->right = delete_min(r);
        return balance_node(temp);
    }
    else if (node->key > key)
        node->left = delete(node->left, key);
    else
        node->right = delete(node->right, key);

    return balance_node(node);
}

node_t *search(node_t *root, int key) {
    node_t *node = root;
    while (node) {
        if (node->key > key)
            node = node->left;
        else if (node->key < key)
            node = node->right;
        else
            return node;
    }
    return 0;
}

node_t **find_most_distant(node_t *node, int key) {
    node_t **nodes = calloc(sizeof(node_t*), 2);
    node_t *max_node = node;
    node_t *min_node = node;

    while (max_node->right)
        max_node = max_node->right;
    while (min_node->left)
        min_node = min_node->left;
    if (abs(max_node->key - key) > abs(min_node->key - key)) 
        nodes[1] = max_node;
    
    else if (abs(max_node->key - key) < abs(min_node->key - key))
        nodes[1] = min_node;
    else {
        nodes[0] = min_node;
        nodes[1] = max_node;
    }
    return nodes;
}

int num_of_digits(int x) {
    int res = 0;
    while (x) {
        x /= 10;
        res += 1;
    }
    return res;
}

void traversal_tree(node_t *node, int num) {
    if (!node) 
        return;
    if (num_of_digits(node->key) == num)
        printf("%d ", node->key);
    traversal_tree(node->left, num);
    traversal_tree(node->right, num);
}

void free_tree(node_t *node) {
    if (!node)
        return;
    if (node->left) 
        free_tree(node->left);
    if (node->right)
        free_tree(node->right);
    free(node->info);
    free(node);
    
}

