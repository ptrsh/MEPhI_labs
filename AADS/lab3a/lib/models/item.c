#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "item.h"

Item *item_create(char *info, char *key1, char *key2) {
    Item *item = (Item*)malloc(sizeof(Item));
    item->info = info;
    item->key1 = key1;
    item->key2 = key2;
    item->release = 0;
    item->next = NULL;
    return item;
}

void item_add(Item **head, Item *item) {
    int max_release;
    while (*head) {
        max_release = (*head)->release;
        head = &(*head)->next;
    }
    (*head) = item;
    (*head)->release = max_release + 1;
    (*head)->next = NULL;
}

void item_free(Item *item) {
    Item *tmp;
    while (item != NULL) {
        tmp = item;
        item = item->next;
        free(tmp->info);
        free(tmp->key1);
        free(tmp->key2);
        free(tmp);
    }
}


