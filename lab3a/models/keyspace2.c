#include "stdio.h"
#include <string.h>
#include <malloc.h>
#include "keyspace2.h"

int find_hash(char *key, int size) {
    int value = 0;

    for (int i = 0; i < strlen(key); ++i) 
        value = ((value * 37) % size + key[i]) % size;

    return value;
}

int keyspace2_check(KeySpace_t *KeySpace, int size, char *key) {
    int hash = find_hash(key, size);
    if (KeySpace->busy[hash] == 0)
        return -1;
    else {
        if (KeySpace->keys[hash]->item->key2 == key)
            return hash;
        else {
            int h = 1;
            int position = hash;
            int visited = 1;

            while ((strcmp(KeySpace->keys[position]->item->key2, key) != 0) && (visited < size)) {
                position = (position + h) % size;
                visited += 1;
            }

            if (visited == size)
                return -2;

            return position;
        }
    }
}

void keyspace2_add(KeySpace_t *KeySpace, int position, int size, Item *item) {
    if (position == -1) {
        Key *Key = key_create(item);
        position = find_hash(item->key2, size);
        KeySpace->keys[position] = Key;
        KeySpace->busy[position] = 1;
        KeySpace->length += 1;
    }
    else {
        Key **head = &(KeySpace->keys[position]);
        int max_release;
        while ((*head)) {
            if (strcmp((*head)->item->key1, item->key1) == 0) {
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

