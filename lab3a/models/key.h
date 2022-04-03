#include "item.h"

#ifndef KEY_H
#define KEY_H

typedef struct Key {
    Item *item;
    int release;
    struct Key *next;
} Key;

Key *key_create(Item* item);
void delete_key_base(Key **head);
void key_free(Key *head);

#endif