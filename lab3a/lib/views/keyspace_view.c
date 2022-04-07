#include <stdio.h>
#include "keyspace_view.h"

void print_keyspace(KeySpace_t *KeySpace, int size) {
    for (int i = 0; i<size; i++)
        if (KeySpace->busy[i] == 1)
            print_key(KeySpace->keys[0]);
    printf("\n");
}
