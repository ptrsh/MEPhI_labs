#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include "keyspaces.h"

KeySpace_t *keyspace_init(int size) {
    KeySpace_t *KeySpace = (KeySpace_t*)malloc(sizeof(KeySpace_t));
    KeySpace->length = 0;
    KeySpace->keys = (Key**)calloc(size, sizeof(Key*));
    KeySpace->busy = (int*)calloc(size, sizeof(int));
    return KeySpace;
}

void delete_in_ks(KeySpace_t *KeySpace, int position) {
    if (KeySpace->busy[position] = 0)
        return;

    KeySpace->busy[position] = 0;
    key_free(KeySpace->keys[position]);
}

void keyspace_free(KeySpace_t *KeySpace, int size) {
    for (int i = 0; i < size; i++) 
        if (KeySpace->busy[i] == 1)
            key_free(KeySpace->keys[i]);
    free(KeySpace->keys);
    free(KeySpace->busy);
    free(KeySpace);
}

