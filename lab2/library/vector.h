#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
    int length;
    char *data;
} vector_t;

void vector_init(vector_t *vector);
void vector_push(vector_t *vector, char data);
void vector_print(vector_t *vector);
void vector_free(vector_t *vector);
int vector_is_empty(vector_t *vector);
char vector_peek(vector_t *vector);
char vector_pop(vector_t *vector);

#endif