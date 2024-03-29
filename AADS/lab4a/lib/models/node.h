#include <stdbool.h>
#include "item.h"

#ifndef NODE_H
#define NODE_H

typedef struct node {
    item *data;
    struct node *left;
    struct node *right;
    bool right_thread; 
    bool left_thread;
} node_t;

node_t *create_node(char *key, int value);
void insert_node(node_t *parent, node_t *child);
node_t *find_least(node_t *node);
void traversal_tree(node_t *node);
int delete(node_t *root, char *key, int version);
node_t **search(node_t *root, char *key);
node_t **find_nearest_max(node_t *node, char *key);
void free_tree(node_t *node);
void write_node(node_t *node);

#endif 
