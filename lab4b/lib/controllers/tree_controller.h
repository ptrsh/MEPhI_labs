#include "../models/node.h"
#include "../views/tree_view.h"

#ifndef TREE_CONTROLLER_H
#define TREE_CONTROLLER_H

node_t *init_tree();
void add_element(node_t **root);
void search_by_key(node_t **root);
void special_search_by_key(node_t **root); 
void delete_by_key(node_t **root); 
void traversal(node_t **root);
void print(node_t **root); 
node_t *load_from_file();
void timing(node_t **node);

#endif