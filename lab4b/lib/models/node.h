#ifndef NODE_H
#define NODE_H

typedef struct node {
    char *info;
    int key;
    struct node *left;
    struct node *right;
} node_t;

node_t *create_node(int key, char *info); 
node_t *insert_node(node_t *parent, node_t *child); 
void traversal_tree(node_t *node, int num); 
node_t *delete(node_t *node, int key); 
node_t *search(node_t *root, int key); 
node_t **find_most_distant(node_t *node, int key); 
void write_node(node_t *node, FILE *file);
void free_tree(node_t *node); 

#endif 
