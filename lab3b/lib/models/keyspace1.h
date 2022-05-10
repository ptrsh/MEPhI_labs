#include "stdlib.h"
#include "item.h"

#ifndef KEYSPACE1_H
#define KEYSPACE1_H

typedef struct KeySpace1 {
    int size;
    int used;
    Item **items;
} KeySpace1;

KeySpace1 *keyspace1_init(int size);
int keyspace1_can_insert(KeySpace1 *this);
int keyspace1_found(KeySpace1 *this, Item **dest, char *key);
void keyspace1_add(KeySpace1 *this, Item *item);
void keyspace1_delete(KeySpace1 *this, char *key);
void keyspace1_free(KeySpace1 *this);

#endif 
