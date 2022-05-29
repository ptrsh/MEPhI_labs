#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
    int size;
    int *data;
} vector_t;

vector_t *vector_init(int size, int fill);
vector_t *vector_push(vector_t *this, int value);
void vector_merge(vector_t *v1, vector_t *v2);
void vector_free(vector_t *this);

#endif 