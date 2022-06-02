#include "../models/graph.h"
#include "../views/graph_view.h"

#ifndef GRAPH_CONTROLLER_H
#define GRAPH_CONTROLLER_H

void vertex_add(graph_t *graph);
void edge_add(graph_t *graph);
void vertex_delete(graph_t *graph);
void edge_delete(graph_t *graph);
void shortest_path_find(graph_t *graph);
void go_dfs(graph_t *graph);
void components_get(graph_t *graph);
void matrix_print(graph_t *graph);
void graph_draw(graph_t *graph);

#endif