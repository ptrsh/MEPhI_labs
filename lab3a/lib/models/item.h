#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
    char *info;
    char *key1;
    char *key2;
    int release;
    struct Item *next;
} Item;

Item *item_create(char *info, char *key1, char *key);
void item_add(Item **head, Item *item);
void item_free(Item *item);
#endif