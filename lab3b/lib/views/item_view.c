#include <stdio.h>
#include "item_view.h"

void print_item(Item *item) {
        if (item) {
            printf("Элементы были найдены!\n\n");
            Item **head = &(item);
            while (*head) {
                printf("Версия элемента: %d\nДанные: %s\nКлюч 1: %s\nКлюч 2: %s\n\n", (*head)->release, (*head)->info, (*head)->key1, (*head)->key2);
                head = &(*head)->next;
        }
    } else
        printf("Элементы с таким составным ключом не найдены!\n");
}