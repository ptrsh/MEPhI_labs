#include <stdio.h>
#include "graph_view.h"

void read_vertex_coordinates(double *x, double *y) {
    printf("Введите координату x вершины:\n");
    *x = read_num("Вы ввели некорректное число!", -10000000.0, 10000000.0);
    printf("Введите координату y вершины:\n");
    *y = read_num("Вы ввели некорректное число!", -10000000.0, 10000000.0);
}
void read_vertex_name(char **name) {
    printf("Введите имя вершины:\n");
    *name = get_str();
}

void print_vector(str_vector *vector) {
    for (int i = vector->size - 1; i >= 0; --i)
        printf("%s ", vector->strings[i]);
    printf("\n");
}

void print_vectors(str_vector **vectors) {
    for (int i = 1; i<=(int)vectors[0]; i++) {
        print_vector(vectors[i]);
    }
}

void print_matrix(graph_t *graph) {
    for (int i = 0; i<graph->size; i++){
        for (int j = 0; j<graph->size; j++)
            printf("%6.1f ", graph->matrix[i][j]);
        printf("\n\n");
    }
}