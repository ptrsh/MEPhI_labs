#include <stdbool.h>

#include "../other/readline.h"
#include "../models/node.h"

#ifndef TREE_VIEW_H
#define TREE_VIEW_H

void init_message(int tree_from_file);
void file_or_input(int *choice);
void read_node(char **key, int *value);
void read_key(char **key);
void read_key_version(char **key, int *version);
void print_nodes(node_t **nodes);
void print_tree(node_t *node, int padding, bool right_branch);
void check_delete(int status);

#endif