#ifndef TABLE_H
#define TABLE_H

#include "keyspace1.h"
#include "keyspace2.h"
#include "keyspaces.h"

typedef struct Table {
    KeySpace_t *ks1;
    KeySpace_t *ks2;
    int ks1_size;
    int ks2_size;
} Table;

Table *table_init(int ks1_size, int ks2_size); 
Table *table_new_from_kp2(Table *table, char *key); 
Item *table_search_by_keys(Table *table, char *key1, char *key2); 
Key *table_search_in_ks1(Table *table, char *key); 
Key *table_search_in_ks2(Table *table, char *key); 
int table_add(Table *table, char *data, char *key1, char *key2); 
void table_delete_by_keys(Table *table, char *key1, char *key2); 
void table_delete_in_ks1(Table *table, char *key); 
void table_delete_in_ks2(Table *table, char *key); 
void table_delete_version_in_ks1(Table *table, char *key, int version); 
void table_reorganise_ks1(Table *table); 
void table_print(Table *table); 
void table_free(Table* table);

#endif