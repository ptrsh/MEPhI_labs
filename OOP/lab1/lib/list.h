#ifndef LIST_H
#define LIST_H

typedef struct list {
    int num;
    int column;
    list *next;
} list;

#endif