#ifndef LIST_H
#define LIST_H

typedef struct node {
    char data;
    struct node *next;
} node;

typedef struct list {
    node *head;
} list_t;

void list_init(list_t *list);
void list_push_front(list_t *list, char data);
void list_free(list_t *list);
void list_print(list_t *list);
int list_is_empty(list_t *list);
char list_peek(list_t *list);
char list_pop(list_t *list);

#endif