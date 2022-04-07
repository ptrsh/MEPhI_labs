#include <stdio.h>
#include "key_view.h"

void print_key(Key *key) {
    if (key) {
        printf("Элементы были найдены!\n\n");
        Key **head = &(key);
        while (*head) {
            Item **head2 = &((*head)->item);
            while (*head2) {
                printf("Версия элемента: %d\nДанные: %s\nКлюч 1: %s\nКлюч 2: %s\nВерсия ключа 1: %d\n\n", (*head2)->release, (*head2)->info, (*head2)->key1, (*head2)->key2, (*head)->release);
                head2 = &(*head2)->next;
            }
            head = &(*head)->next;
        }
    } else
        printf("Элементы с таким ключом не найдены!\n");

}


