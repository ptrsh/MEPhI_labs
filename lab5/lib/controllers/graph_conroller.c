#include <stdio.h>
#include <malloc.h>
#include "graph_controller.h"

void vertex_add(graph_t *graph) {
    char *name;
    double x, y;
    read_vertex_name(&name);
    read_vertex_coordinates(&x, &y);
    add_vertex(graph, name, x, y);
}

void edge_add(graph_t *graph) {
    char *name1, *name2;
    read_vertex_name(&name1);
    read_vertex_name(&name2);
    add_edge(graph, name1, name2);
    free(name1);
    free(name2);
}

void vertex_delete(graph_t *graph){
    char *name;
    read_vertex_name(&name);
    delete_vertex(graph, name);
    free(name);
}

void edge_delete(graph_t *graph) {
    char *name1, *name2;
    read_vertex_name(&name1);
    read_vertex_name(&name2);
    delete_edge(graph, name1, name2);
    free(name1);
    free(name2);
}

void shortest_path_find(graph_t *graph) {
    char *name1, *name2;
    read_vertex_name(&name1);
    read_vertex_name(&name2);
    str_vector *result = find_shortest_path(graph, name1, name2);
    if (!result)
        printf("Между вершинами нет пути!\n");
    else {
        print_vector(result);
        str_vector_free(result);
    }
    free(name1);
    free(name2);
}

void go_dfs(graph_t *graph) {
    char *name1, *name2;
    read_vertex_name(&name1);
    read_vertex_name(&name2);
    str_vector *result = get_dfs(graph, name1, name2);
    if (!result)
        printf("Между вершинами нет пути!\n");
    else {
        print_vector(result);
        str_vector_free(result);
    }
    free(name1);
    free(name2);
}

void components_get(graph_t *graph) {
    str_vector **result = get_connections(graph);
    print_vectors(result);
    for (int i = 1; i<=(int)result[0]; i++) {
        str_vector_free(result[i]);
    }
    free(result);
}

void load_city(graph_t *graph) {
    FILE *file = fopen("city.csv", "r");
    char *str = get_str_file(file);
    free(str);
    while (str = get_str_file(file)) {
        if (str) {
            city_t *city = city_parse(str);
            add_vertex(graph, city->name, city->x, city->y);
            for (int i = 0; i <graph->size - 1; i++) 
                if (rand() % 8 == 0) add_edge(graph, city->name, graph->vertex[i].name);
            free(city);
        }
    }
       
    free(str);
    fclose(file);  
} 

void matrix_print(graph_t *graph) {
    print_matrix(graph);
}

void graph_draw(graph_t *graph) {
    draw_graph(graph);
}