#include "stdlib.h"
#include "vector.h"

vector_t *vector_init(int size, int fill) {
    vector_t *this = malloc(sizeof(vector_t));
    this->size = size;
    this->data = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) this->data[i] = fill;
    return this;
}

void vector_enlarge(vector_t *this) {
    this->data = realloc(this->data, (this->size + 1) * sizeof(int));
    this->data[this->size++] = 0;
}

vector_t *vector_push(vector_t *this, int value) {
    if (this == NULL) return this;
    vector_enlarge(this);
    this->data[this->size - 1] = value;
    return this;
}

void vector_merge(vector_t *v1, vector_t *v2) {
    for (int i = 0; i < v2->size; i++) vector_push(v1, v2->data[i]);
    vector_free(v2);
}

void vector_free(vector_t *this) {
    if (this == NULL) return;
    free(this->data);
    free(this);
    this = NULL;
}
