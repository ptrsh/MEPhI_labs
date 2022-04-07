#include <stdio.h>
#include <malloc.h>
#include "key.h"

Key *key_create(Item* item) {
    Key* key = (Key*)malloc(sizeof(Key));
    key->item = item;
    key->release = 0;
    key->next = NULL;
    return key;
}

void delete_key_base(Key **head) {
    Key *tmp = (*head);
    (*head) = (*head)->next;
    item_free(tmp->item);
    free(tmp);
    while (*head) {
        (*head)->release -= 1;
        head = &(*head)->next;
    }
}

void key_free(Key *head) {
    Key *tmp;
    while (head != NULL) {
       tmp = head;
       head = head->next;
       item_free(tmp->item);
       free(tmp);
    }
    
}