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

void str_vector_free(str_vector *vector) {
    free(vector->strings);
    free(vector);
}