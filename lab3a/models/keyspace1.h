#include "keyspaces.h"
#include "key.h"

#ifndef KEYSPACE1_H
#define KEYSPACE1_H

int keyspace1_check(KeySpace_t *KeySpace, int size, char *key);
void keyspace1_add(KeySpace_t *KeySpace, int position, Item *item);
void keyspace1_push_back(KeySpace_t *KeySpace, Item *item);
int keyspace1_reorganise(KeySpace_t *KeySpace, int size);

#endif