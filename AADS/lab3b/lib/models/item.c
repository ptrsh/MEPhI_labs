#include "stdlib.h"
#include "stdint.h"

#include "../other/item_helper.h"
#include "../models/item.h"

Item *item_init(char *info, char *key1, char *key2) {
    Item *this = malloc(sizeof(Item));
    this->info = info;
    this->key1 = key1;
    this->key2 = key2;
    this->version = 0;
    this->next = NULL;
    unsigned long ptr = file_add_item(this);
    item_free(this);
    return ptr;
}

Item *item_dup(Item *this) {
    this = file_load_item(this);
    unsigned long ptr = file_add_item(this);
    if (this->next != NULL) {
        unsigned long next = item_dup(this->next);
        this->next = NULL;
        file_update_item(this, ptr);
        item_add(ptr, next);
    }
    item_free(this);
    return ptr;
}

Item *item_get_next(Item *this) {
    
    if (this->next == NULL) {
        item_free(this);
        return NULL;
    }
    Item *next = file_load_item(this->next);
    item_free(this);
    return next;
}

void item_add(Item *this, Item *next) {
    
    
    unsigned long ptr1 = this;
    unsigned long ptr2 = next;
    this = file_load_item(this);
    if (this->next != NULL) {
        item_add(this->next, next);
    } else {
        next = file_load_item(next);
        this->next = ptr2;
        next->version = this->version + 1;
        file_update_item(this, ptr1);
        file_update_item(next, ptr2);
        item_free(next);
    }
    item_free(this);
}

void item_free(Item *this) {
    
    free(this->info);
    free(this->key1);
    free(this->key2);
    free(this);
}
