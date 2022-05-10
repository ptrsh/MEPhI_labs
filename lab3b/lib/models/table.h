#include "keyspace1.h"
#include "keyspace2.h"

#ifndef TABLE_H
#define TABLE_H

typedef struct Table {
    KeySpace1 *keySpace1;
    KeySpace2 *keySpace2;
} Table;

Table *table_init(int size1, int size2);
int table_enough_space(Table *this);
int table_keypair_found(Table *this, Item **dest, char *key1, char *key2);
int table_keypair_found_ks1(Table *this, Item **dest, char *key);
int table_keypair_found_ks2(Table *this, Item **dest, char *key);
void table_add(Table *this, Item *item);
void table_reorganise(Table *this);
void table_delete_by_keys(Table *this, char *key1, char *key2);
void table_delete_by_key1(Table *this, char *key);
void table_delete_by_key2(Table *this, char *key);
void table_free(Table *this);

#endif 
