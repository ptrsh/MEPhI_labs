#include "key.h"

#ifndef KEYSPACE_H
#define KEYSPACE_H

typedef struct KeySpace {
    int length;
    int *busy;
    Key **keys;
} KeySpace_t;

KeySpace_t *keyspace_init(int size);
void delete_in_ks(KeySpace_t *KeySpace, int position);
void keyspace_free(KeySpace_t *KeySpace, int size);

#endif