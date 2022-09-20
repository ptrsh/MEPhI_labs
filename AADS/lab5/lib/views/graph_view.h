#include "../models/string_vector.h"
#include "../models/graph.h"
#include "../other/readline.h"

#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

void read_vertex_coordinates(double *x, double *y);
void read_vertex_name(char **name);
void print_vector(str_vector *vector);
void print_vectors(str_vector **vectors);
void print_matrix(graph_t *graph);

#endif