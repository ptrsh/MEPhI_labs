#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "keyspace1.h"

int keyspace1_check(KeySpace_t* KeySpace, int size, char *key) {
    for (int i=0; i < size; i++) {
        if (KeySpace->busy[i] == 1)
            if(strcmp(KeySpace->keys[i]->item->key1, key) == 0)
                return i;
    }
    if (KeySpace->length != size)
        return -1;
    return -2;
}

void keyspace1_add(KeySpace_t *KeySpace, int position, Item *item) {
    if (position == -1) {
        Key *Key = key_create(item);
        KeySpace->keys[KeySpace->length] = Key;
        KeySpace->busy[KeySpace->length] = 1;
        KeySpace->length += 1;
    }
    else {
        Key **head = &(KeySpace->keys[position]);
        int max_release;
        while ((*head)) {
            if (strcmp((*head)->item->key2, item->key2) == 0) {
                item_add(&((*head)->item), item);
                return;
            }
            max_release = (*head)->release;
            head = &(*head)->next;
        }
        
        Key *Key = key_create(item);
        (*head) = Key;
        (*head)->release = max_release + 1;
        (*head)->next = NULL;
    }
        
}

int keyspace1_reorganise(KeySpace_t *KeySpace, int size) {
    if (KeySpace->length == size)
        return size;
    
    int real_length = 0;
    int real_key = 0;

    for (int source_index = 0; source_index < size; source_index++) {
        if (KeySpace->busy[source_index] == 1) {
            KeySpace->busy[real_length++] = KeySpace->busy[source_index];
            KeySpace->keys[real_key++] = KeySpace->keys[source_index];
        }
    }

    for (int i = real_length; i < size; i++)
        if (KeySpace->busy[i] == 1) {
            key_free(KeySpace->keys[i]);
            KeySpace->busy[i] = 0;
        }

    KeySpace->length = real_length;
    return real_length;


}