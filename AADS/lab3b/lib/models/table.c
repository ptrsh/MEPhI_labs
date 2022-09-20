#include "../other/common_helper.h"
#include "../other/item_helper.h"
#include "../other/keyspace1_helper.h"
#include "../other/keyspace2_helper.h"
#include "table.h"

Table *table_init(int size1, int size2) {
    Table *this = malloc(sizeof(Table));
    this->keySpace1 = keyspace1_init(size1);
    this->keySpace2 = keyspace2_init(size2);
    return this;
}

int table_enough_space(Table *this) {
    return keyspace1_can_insert(this->keySpace1) && keyspace2_can_insert(this->keySpace2);
}

int table_keypair_found(Table *this, Item **dest, char *key1, char *key2) {
    
    unsigned long item1, item2;
    if (keyspace1_found(this->keySpace1, &item1, key1) == 0) return 0;
    if (keyspace2_found(this->keySpace2, &item2, key2) == 0) return 0;
    if (item1 == item2) {
        *dest = item1;
        return 1;
    }
    return 0;
}

int table_keypair_found_ks1(Table *this, Item **dest, char *key) {
    return keyspace1_found(this->keySpace1, dest, key);
}

int table_keypair_found_ks2(Table *this, Item **dest, char *key) {
    return keyspace2_found(this->keySpace2, dest, key);
}

void table_add(Table *this, Item *item) {
    keyspace1_add(this->keySpace1, item);
    keyspace2_add(this->keySpace2, item);
}

void table_delete_by_keys(Table *this, char *key1, char *key2) {
    Item *item;
    if (table_keypair_found(this, &item, key1, key2) == 1) {
        keyspace1_delete(this->keySpace1, key1);
        keyspace2_delete(this->keySpace2, key2);
    }
}

void table_delete_by_key1(Table *this, char *key) {
    Item *item;
    if (keyspace1_found(this->keySpace1, &item, key) == 1) {
        item = file_load_item(item);
        table_delete_by_keys(this, item->key1, item->key2);
        item_free(item);
    }
}

void table_delete_by_key2(Table *this, char *key) {
    Item *item;
    if (keyspace2_found(this->keySpace2, &item, key) == 1) {
        item = file_load_item(item);
        table_delete_by_keys(this, item->key1, item->key2);
        item_free(item);
    }
}

void table_reorganise(Table *table) {
    unsigned long ptr = table->keySpace2;

    KeySpace2 *KeySpace = file_load_keyspace1(table->keySpace2);
    if (KeySpace->used == KeySpace->size)
        return;
    
    int real_length = 0;
    int real_key = 0;

    for (int source_index = 0; source_index < KeySpace->size; source_index++) {
        if (KeySpace->busy[source_index] == 1) {
            KeySpace->busy[real_length++] = KeySpace->busy[source_index];
            KeySpace->items[real_key++] = KeySpace->items[source_index];
        }
    }

    for (int i = real_length; i < KeySpace->size; i++)
        if (KeySpace->busy[i] == 1) {
            item_free(KeySpace->items[i]);
            KeySpace->busy[i] = 0;
        }

    KeySpace->used = real_length;
    return;
}

void table_free(Table *this) {
    free(this);
}