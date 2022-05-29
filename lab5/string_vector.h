#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

typedef struct str_vector {
    size_t size;
    char **strings;
} str_vector;

void str_vector_init(str_vector *vector);
void str_vector_add(str_vector *vector, char *text);
void str_vector_print(str_vector *vector);
void str_vector_back_print(str_vector *vector);
void str_vector_free(str_vector *vector);

#endif