#include <stdio.h>
#include <malloc.h>
#include "vector.h"

void vector_init(vector_t *vector) {
    vector->length = 0;
    vector->data = (char*)malloc(sizeof(char));
}

void vector_push(vector_t *vector, char data) {
    vector->length += 1;
    vector->data = (char*)realloc(vector->data, vector->length * sizeof(char*));
    (vector->data)[vector -> length - 1] = data;
}

void vector_print(vector_t *vector) {
    for (int i = vector->length - 1; i >= 0; --i)
        printf("%c ", (vector->data)[i]);
    printf("\n");
}

void vector_free(vector_t *vector) {
    free(vector->data);
}

int vector_is_empty(vector_t *vector) {
    return vector->length == 0 ? 1 : 0;
}

char vector_peek(vector_t *vector) {
    if (vector->length == 0)
        return 0;
    return vector->data[vector->length - 1];
}

char vector_pop(vector_t *vector) {
    char data = vector->data[vector->length - 1];
    vector->data = (char*)realloc(vector->data, (vector->length - 1) * sizeof(char));
    vector->length -= 1;
    return data;
}