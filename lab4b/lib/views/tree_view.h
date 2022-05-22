#include <stdbool.h>

#include "../other/readline.h"
#include "../models/node.h"

#ifndef TREE_VIEW_H
#define TREE_VIEW_H

void init_message(int tree_from_file);
void file_or_input(int *choice);
void read_node(int *key, char **info);
void read_key(int *key);
void read_number(int *num);
void print_nodes(node_t **nodes);
void print_node(node_t *node);
void print_tree(node_t *node, int padding, bool right_branch);

#endif