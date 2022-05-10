#include "stdint.h"
#include "string.h"

#include "../other/item_helper.h"
#include "../other/keyspace2_helper.h"
#include "keyspace2.h"

const int PRIMES[32] = {
        2, 3, 5, 7, 11, 13, 17, 19,
        23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89,
        97, 101, 103, 107, 109, 113, 127, 131
};

uint64_t hash1(char *str) {
    uint64_t hash = 0;
    for (int i = 0; i < strlen(str); i++)
        hash += PRIMES[i] * str[i];
    return hash;
}

uint64_t hash2(char *str, int size) {
    uint64_t hash = 1;
    int seed = 0;
    for (int i = 0; i < strlen(str); i++) {
        srand(seed + str[i]);
        seed = rand() % 32;
        if (size % PRIMES[seed] != 0)
            hash *= PRIMES[seed];
    }
    return hash;
}

int find_position(KeySpace2 *this, char *key) {
    
    this = file_load_keyspace2(this);
    int size = this->size;
    uint64_t h1 = hash1(key), h2 = hash2(key, size);
    int hash = 0, viewed = -1;
    do {
        viewed++;
        hash = (int) ((h1 + viewed * h2) % size);
    } while (viewed < size && this->busy[hash] == 1);
    keyspace2_free(this);
    if (viewed < size)
        return hash;
    return -1;
}

int find_item_position(KeySpace2 *this, char *key) {
    
    this = file_load_keyspace2(this);
    int size = this->size;
    uint64_t h1 = hash1(key), h2 = hash2(key, size);
    int hash = 0, viewed = -1;
    do {
        viewed++;
        hash = (int) ((h1 + viewed * h2) % size);
        if (this->busy[hash] != 0) {
            Item *item = file_load_item(this->items[hash]);
            if (strcmp(item->key2, key) == 0) {
                item_free(item);
                break;
            }
            item_free(item);
        }
    } while (viewed < size);
    keyspace2_free(this);
    if (viewed < size)
        return hash;
    return -1;
}

KeySpace2 *keyspace2_init(int size) {
    KeySpace2 *this = malloc(sizeof(KeySpace2));
    this->items = calloc(size, sizeof(Item *));
    this->busy = calloc(size, sizeof(int));
    this->size = size;
    this->used = 0;
    unsigned long ptr = file_append_keyspace2(this);
    keyspace2_free(this);
    return ptr;
}

int keyspace2_can_insert(KeySpace2 *this) {
    
    unsigned long ptr = this;
    this = file_load_keyspace2(this);
    int res = this->used < this->size;
    keyspace2_free(this);
    return res;
}

int keyspace2_found(KeySpace2 *this, Item **dest, char *key) {
    
    
    int pos = find_item_position(this, key);
    this = file_load_keyspace2(this);
    if (pos != -1) {
        *dest = this->items[pos];
        keyspace2_free(this);
        return 1;
    }
    keyspace2_free(this);
    return 0;
}

void keyspace2_add(KeySpace2 *this, Item *item) {
    
    
    unsigned long ptr = this;
    unsigned long itemPtr = item;
    item = file_load_item(item);
    int pos = find_position(this, item->key2);
    this = file_load_keyspace2(this);
    this->items[pos] = itemPtr;
    this->busy[pos] = 1;
    this->used++;
    file_update_keyspace2(this, ptr);
    keyspace2_free(this);
    item_free(item);
}

void keyspace2_delete(KeySpace2 *this, char *key) {
    
    unsigned long ptr = this;
    this = file_load_keyspace2(this);
    int pos = find_item_position(ptr, key);
    if (pos != -1) {
        this->busy[pos] = 0;
        this->used--;
        file_update_keyspace2(this, ptr);
    }
    keyspace2_free(this);
}

void keyspace2_free(KeySpace2 *this) {
    free(this->items);
    free(this->busy);
    free(this);
}