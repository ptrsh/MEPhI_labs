#include <stdio.h>
#include <malloc.h>
#include "string_vector.h"

void str_vector_init(str_vector *vector) {
    vector->size = 0;
    vector->strings = malloc(sizeof(char*));
}

void str_vector_add(str_vector *vector, char *text) {
    vector->strings[vector->size] = text;
    vector->size += 1;
    vector->strings = realloc(vector->strings, sizeof(char*)*(vector->size + 1));
}

void str_vector_print(str_vector *vector) {
    for (int i = 0; i < vector->size; ++i)
        printf("%s ", vector->strings[i]);
    printf("\n");
}

void str_vector_back_print(str_vector *vector) {
    for (int i = vector->size - 1; i >= 0; --i)
        printf("%s ", vector->strings[i]);
    printf("\n");
}

void str_vector_free(str_vector *vector) {
    free(vector->strings);
    free(vector);
}