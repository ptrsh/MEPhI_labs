#include "../models/table.h"

#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

Table *read_table_size();
Item *read_element();
void read_keys(char **key1, char **key2);
void read_key(char **key);
void table_print(Table *this);

#endif 