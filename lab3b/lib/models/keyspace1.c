#include "string.h"

#include "../other/item_helper.h"
#include "../other/keyspace1_helper.h"
#include "keyspace1.h"

KeySpace1 *keyspace1_init(int size) {
    KeySpace1 *this = malloc(sizeof(KeySpace1));
    this->items = calloc(size, sizeof(unsigned long));
    this->size = size;
    this->used = 0;
    unsigned long ptr = file_add_keyspace1(this);
    keyspace1_free(this);
    return ptr;
}

int keyspace1_can_insert(KeySpace1 *this) {
    
    this = file_load_keyspace1(this);
    int res = this->used < this->size;
    keyspace1_free(this);
    return res;
}

int keyspace1_found(KeySpace1 *this, Item **dest, char *key) {
    
    
    this = file_load_keyspace1(this);
    for (int i = 0; i < this->used; i++) {
        Item *item = file_load_item(this->items[i]);
        if (strcmp(item->key1, key) == 0) {
            *dest = this->items[i];
            item_free(item);
            keyspace1_free(this);
            return 1;
        }
        item_free(item);
    }
    keyspace1_free(this);
    return 0;
}

void keyspace1_add(KeySpace1 *this, Item *item) {
    
    
    unsigned long ptr = this;
    this = file_load_keyspace1(this);
    this->items[this->used++] = item;
    file_update_keyspace1(this, ptr);
    keyspace1_free(this);
}

KeySpace1 *keySpace1Range(KeySpace1 *this, char *key1, char *key2) {
    
    this = file_load_keyspace1(this);
    KeySpace1 *keySpace = keyspace1_init(this->used);
    for (int i = 0; i < this->used; i++) {
        Item *item = file_load_item(this->items[i]);
        if (strcmp(item->key1, key1) >= 0 && strcmp(item->key2, key2) <= 0)
            keyspace1_add(keySpace, item_dup(this->items[i]));
        item_free(item);
    }
    keyspace1_free(this);
    return keySpace;
}

void keyspace1_delete(KeySpace1 *this, char *key) {
    
    unsigned long ptr = this;
    this = file_load_keyspace1(this);
    for (int i = 0; i < this->used; i++) {
        Item *item = file_load_item(this->items[i]);
        if (strcmp(item->key1, key) == 0) {
            for (int j = i; j + 1 < this->size && j < this->used; j++)
                this->items[j] = this->items[j + 1];
            this->used--;
            file_update_keyspace1(this, ptr);
            item_free(item);
            break;
        }
        item_free(item);
    }
    keyspace1_free(this);
}

void keyspace1_free(KeySpace1 *this) {
    free(this->items);
    free(this);
}