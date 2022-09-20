#include <iostream>
#include "matrix.h"
#include "utils.h"

void push(matrix_t *matrix, int row, int column, int num) {
    if (!matrix->data[row]) {
        matrix->data[row] = new list;
        matrix->data[row]->column = column;
        matrix->data[row]->num = num;
        matrix->data[row]->next = nullptr;
    }
    else {
        list *tmp = matrix->data[row];
        while(tmp->next != nullptr) tmp = tmp->next;
        list *node = new list;
        node->column = column;
        node->num = num;
        node->next = nullptr;
        tmp->next = node;
    }
}

matrix_t *init(int m, int n) {
    matrix_t *matrix = new matrix_t;
    matrix->rows = m;
    matrix->columns = n;
    matrix->data = new list*[m];
    for (int i = 0; i < matrix->rows; i++) matrix->data[i] = NULL;
    return matrix;
}

void scan(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            int num = read_num();
            if (num != 0) push(matrix, i, j, num);
        }   
    }
}

void print(matrix_t *matrix, std::string message) {
    std::cout << "\n\n" << message << "\n";
    for (int i = 0; i < matrix->rows; i++) {
        list *tmp = matrix->data[i];
        if (tmp) {
            int current = 0;
            int count = matrix->columns;
            while (tmp) {
                for (int i = current; i < tmp->column; i++) {
                    std::cout << 0 << " ";
                    count -= 1;
                }
                std::cout << tmp->num << " ";
                current = tmp->column + 1;
                tmp = tmp->next;
                count -= 1;
            }
            for (int i = 0; i < count; i++) std::cout << 0 << " ";
        }
        else for (int i = 0; i < matrix->columns; i++) std::cout << 0 << " ";
        std::cout << "\n";
    }    
}

void fill_new_matrix(matrix_t *old_matrix, matrix_t *new_matrix) {
    for (int i = 0; i < old_matrix->rows; i++) {
        list *tmp = old_matrix->data[i];
        while (tmp) {
            push(new_matrix, i, tmp->column, reverse(tmp->num));
            tmp = tmp->next;
        }
    }
}

void free_matrix(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        if (matrix->data[i]) {
            while(matrix->data[i]->next) {
                list *tmp = matrix->data[i];
                matrix->data[i] = matrix->data[i]->next;
                delete tmp;
            }
            delete matrix->data[i];
        }
    }
    delete []matrix->data;
    delete matrix;
}
