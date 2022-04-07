#include "../other/readline.h"

#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

void read_table_size(int *ks1_size, int *ks2_size);
void read_element(char **data, char **key1, char **key2);
void read_keys(char **key1, char **key2);
void read_key(char **key);
void check_delete(int result);
void read_key_version(char **key, int *version);
void check_add(int result);
#endif