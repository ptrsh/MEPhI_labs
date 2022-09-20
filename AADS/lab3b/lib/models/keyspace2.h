#include "stdlib.h"
#include "item.h"

#ifndef KEYSPACE2_H
#define KEYSPACE2_H

typedef struct KeySpace2 {
    int size;
    int used;
    int *busy;
    Item **items;
} KeySpace2;

KeySpace2 *keyspace2_init(int size);
int keyspace2_can_insert(KeySpace2 *this);
int keyspace2_found(KeySpace2 *this, Item **dest, char *key);
void keyspace2_add(KeySpace2 *this, Item *item);
void keyspace2_delete(KeySpace2 *this, char *key);
void keyspace2_free(KeySpace2 *this);

#endif 