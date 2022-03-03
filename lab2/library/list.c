#include <stdio.h>
#include <malloc.h>
#include "list.h"

void list_init(list_t *list) {
    list->head = NULL;
}

void list_push_front(list_t *list, char data) {
    node *tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = list->head;
    list->head = tmp;
}

void list_print(list_t *list) {
    node *tmp = list->head;
    while (tmp != NULL) {
        printf("%c ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void list_free(list_t *list) {
    while (list->head != NULL) {
        node *tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
}

int list_is_empty(list_t *list) {
    if (list->head == NULL)
        return 1;
    return 0;
}

char list_peek(list_t *list) {
    if (list->head == NULL)
        return 0;
    return list->head->data;
}

char list_pop(list_t *list) {
    if (list->head == NULL)
        return 0;
    char data;
    node *tmp = list->head;
    data = tmp->data;
    list->head = list->head->next;
    free(tmp);
    return data;
}

