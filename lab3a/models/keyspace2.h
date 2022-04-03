#include "keyspaces.h"
#include "key.h"

#ifndef KEYSPACE2_H
#define KEYSPACE2_H


int keyspace2_check(KeySpace_t *KeySpace, int size, char *key);
void keyspace2_add(KeySpace_t *KeySpace, int position, int size, Item *item);

#endif
