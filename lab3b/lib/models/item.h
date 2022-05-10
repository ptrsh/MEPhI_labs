#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
    char *info;
    char *key1;
    char *key2;

    int version;
    struct Item *next;
} Item;

Item *item_init(char *info, char *key1, char *key2);
Item *item_dup(Item *this);
Item *item_get_next(Item *this);

void item_add(Item *this, Item *next);
void item_free(Item *this);

#endif 
