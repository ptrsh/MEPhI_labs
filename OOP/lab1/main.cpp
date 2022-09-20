#include <iostream>
#include <cstring>
#include "lib/matrix.h"
#include "lib/utils.h"

int main() {
    int m, n;
    std::cout << "Введите количество строк:" << std::endl;
    m = read_num();
    std::cout << "Введите количество стобцов:" << std::endl;
    n = read_num();

    matrix_t *matrix = init(m, n);
    matrix_t *new_matrix = init(m, n);

    scan(matrix);
    fill_new_matrix(matrix, new_matrix);

    print(matrix, "Исходная матрица:");
    print(new_matrix, "Новая матрица:");

    free_matrix(matrix);
    free_matrix(new_matrix);
}