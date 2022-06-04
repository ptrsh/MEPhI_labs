#include "malloc.h"
#include "stdio.h"
#include "extra_node.h"

Node *nodeInit(unsigned key, unsigned value) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->height = 1;
    node->right = node->left = NULL;
    return node;
}

void node_update_height(Node *this) {
    unsigned left = this->left ? this->left->height : 0;
    unsigned right = this->right ? this->right->height : 0;
    this->height = (left > right ? left : right) + 1;
}

int node_balance_factor(Node *this) {
    unsigned left = this->left ? this->left->height : 0;
    unsigned right = this->right ? this->right->height : 0;
    return right - left;
}

Node *node_rotate_right(Node *this) {
    Node *res = this->left;
    this->left = res->right;
    res->right = this;
    node_update_height(this);
    node_update_height(res);
    return res;
}

Node *node_rotate_left(Node *this) {
    Node *res = this->right;
    this->right = res->left;
    res->left = this;
    node_update_height(this);
    node_update_height(res);
    return res;
}

Node *nodeBalance(Node *this) {
    node_update_height(this);
    if (node_balance_factor(this) == 2) {
        if (node_balance_factor(this->right) < 0)
            this->right = node_rotate_right(this->right);
        return node_rotate_left(this);
    }
    if (node_balance_factor(this) == -2) {
        if (node_balance_factor(this->left) > 0)
            this->left = node_rotate_left(this->left);
        return node_rotate_right(this);
    }
    return this;
}

Node *nodeInsert(Node *this, unsigned key, unsigned value) {
    if (this == NULL) return nodeInit(key, value);
    if (this->key > key) this->left = nodeInsert(this->left, key, value);
    if (this->key < key) this->right = nodeInsert(this->right, key, value);
    return nodeBalance(this);
}

Node *nodeSearch(Node *this, unsigned key) {
    if (this == NULL) return NULL;
    if (this->key > key) return nodeSearch(this->left, key);
    if (this->key < key) return nodeSearch(this->right, key);
    return this;
}

void nodeFree(Node *this) {
    if (this == NULL) return;
    nodeFree(this->left);
    nodeFree(this->right);
    free(this);
    this = NULL;
}