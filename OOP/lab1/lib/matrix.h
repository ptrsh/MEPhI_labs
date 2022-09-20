#include "list.h"

#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix {
    int rows;
    int columns;
    list **data;
} matrix_t;

matrix_t *init(int m, int n);
void scan(matrix_t *matrix);
void push(matrix_t *matrix, int row, int column, int num);
void print(matrix_t *matrix, std::string message);
void fill_new_matrix(matrix_t *old_matrix, matrix_t *new_matrix);
void free_matrix(matrix_t *matrix);

#endif