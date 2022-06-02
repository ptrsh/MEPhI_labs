#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "string_vector.h"

graph_t *init_graph() {
    graph_t *graph = malloc(sizeof(graph_t));
    graph->size = 0;
    graph->vertex = malloc(sizeof(vertex_t));
    graph->matrix = malloc(sizeof(double *));
    return graph;
}

void add_vertex(graph_t *graph, char *name, double x, double y) {
    graph->vertex[graph->size].name = name;
    graph->vertex[graph->size].x = x;
    graph->vertex[graph->size].y = y;
    graph->size += 1;
    graph->vertex = realloc(graph->vertex, sizeof(vertex_t) * (graph->size + 1));
    graph->matrix = realloc(graph->matrix, sizeof(double*)*graph->size);
    graph->matrix[graph->size - 1] = calloc(graph->size, sizeof(double));
    for (int i = 0; i<graph->size - 1; i++) {
        graph->matrix[i] = realloc(graph->matrix[i], sizeof(double)*(graph->size));
        graph->matrix[i][graph->size-1] = 0;
    }
}

double get_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2),2));
}

void get_position(graph_t *graph, char *name1, char *name2, int *pos1, int *pos2) {
    int position1 = -1;
    int position2 = -1;
    for (int i = 0; i < graph->size; i++) {
        if (strcmp(graph->vertex[i].name, name1)==0)
            position1 = i;
        if (strcmp(graph->vertex[i].name, name2)==0)
            position2 = i;        
    }
    *pos1 = position1;
    *pos2 = position2;
}

void add_edge(graph_t *graph, char *name1, char *name2) {
    int position1;
    int position2;
    get_position(graph, name1, name2, &position1, &position2);
    if ((position1 > -1) && (position2 > -1)) {
        double weight = get_distance(graph->vertex[position1].x, graph->vertex[position1].y,\
                                    graph->vertex[position2].x, graph->vertex[position2].y);
        graph->matrix[position1][position2] = weight;
        graph->matrix[position2][position1] = weight;
    }
}

void delete_column(double **matrix, int position, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = position; j < size - 1; j++)
            matrix[i][j] = matrix[i][j+1]; 
    }
}

void delete_row(double **matrix, int position, int size) {
    for (int i = position; i < size - 1; i++) {
        for (int j = 0; j < size; j++) 
           matrix[i][j] = matrix[i+1][j];
    }
}

void delete_vertex(graph_t *graph, char *name) {
    int position = -1;
    for (int i = 0; i < graph->size; i++) {
        if (strcmp(graph->vertex[i].name, name) == 0) {
            position = i;
            for (int j = position; j < graph->size - 1; j++) 
                graph->vertex[j] = graph->vertex[j+1];
            free(graph->vertex[position].name);
            graph->vertex = realloc(graph->vertex, sizeof(vertex_t) * (graph->size-1));
            break;
        }
    }
    if (position > -1) {
        delete_column(graph->matrix, position, graph->size);
        delete_row(graph->matrix, position, graph->size);  
        graph->size -= 1;
        for (int i = 0; i < graph->size; i++)
            graph->matrix[i] = realloc(graph->matrix[i], sizeof(double)*graph->size);
        
        free(graph->matrix[graph->size]);
        graph->matrix = realloc(graph->matrix, sizeof(double*)*graph->size);
    }
}

void delete_edge(graph_t *graph, char *name1, char *name2) {
    int position1;
    int position2;
    get_position(graph, name1, name2, &position1, &position2);

    if ((position1 > -1) && (position2 > -1)) {
        graph->matrix[position1][position2] = 0;
        graph->matrix[position2][position1] = 0;
    }
}

void free_graph(graph_t *graph) {
    for (int i=0; i<graph->size;i++) {
        free(graph->matrix[i]);
        free(graph->vertex[i].name);
    }
    free(graph->vertex);
    free(graph->matrix);
    free(graph);
}

void draw_graph(graph_t *graph) {
    FILE *file = fopen("graph.dot", "w");
    fprintf(file, "strict graph { node [shape=ellipse style=filled] ");
    int *used = calloc(1, sizeof(int)*graph->size);

    for (int i = 0; i < graph->size; i++)
        if (used[i] == 0) 
            fprintf(file, "\"%s\" ", graph->vertex[i].name);

    for (int u = 0; u < graph->size; u++) {
        for (int v = 0; v < graph->size; v++) {
            if (graph->matrix[u][v] != 0) {
                used[u] = 1;
                used[v] = 1;
                fprintf(file, "\"%s\"--\"%s\" [label=%.2f] ", graph->vertex[u].name, graph->vertex[v].name, graph->matrix[u][v]);
            }
        }
    }

    fprintf(file, "}");
    free(used);
    fclose(file);
    system("dot graph.dot -Tpng -o graph.png");
    printf("Граф успешно создан в graph.png\n");
}

str_vector *dfs(graph_t *graph, int start, int end, int visited[]) {
    if (graph->matrix[start][end] != 0) {
        str_vector *tmp = malloc(sizeof(str_vector));
        str_vector_init(tmp);
        str_vector_add(tmp, graph->vertex[end].name);
        return tmp;
    }

    visited[start] = 1;

    for (int i = 0; i < graph->size; i++) {
        if ((graph->matrix[start][i] == 0) || (visited[i] == 1))
            continue;
        str_vector *result = dfs(graph, i, end, visited);
        if (result != NULL){
            str_vector_add(result, graph->vertex[i].name);
            return result;
        }
    }
    return NULL;
}

str_vector *get_dfs(graph_t *graph, char *name1, char *name2) {
    int start;
    int end;
    get_position(graph, name1, name2, &start, &end);
    int *visited = calloc(graph->size, sizeof(int));
    str_vector *res = dfs(graph, start, end, visited);
    free(visited);
    if (!res)
        return 0;
    str_vector_add(res, graph->vertex[start].name);
    return res;
}

str_vector *find_shortest_path(graph_t *graph, char *name1, char *name2) {
    str_vector *vector = malloc(sizeof(str_vector));
    str_vector_init(vector);
    int start;
    int end;
    get_position(graph, name1, name2, &start, &end);
    int dist[graph->size];
    int parent[graph->size];
   
    for (int i = 0; i < graph->size; i++) {
        dist[i] = 2147483647;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int i = 0; i < graph->size - 1; i++) {
        for (int u = 0; u < graph->size; u++) {
            for (int v = 0; v < graph->size; v++) {
                int weight = graph->matrix[u][v];
                if ((weight == 0) || (dist[u] == 2147483647))
                    continue;
                if (dist[v] > dist[u] + weight) {
                    parent[v] = u;
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    int v = parent[end];
    str_vector_add(vector, graph->vertex[end].name);
    while (v != start) {
        if (v == -1) {
            str_vector_free(vector);
            return 0;
        }
        str_vector_add(vector, graph->vertex[v].name);
        v = parent[v];
    }

    str_vector_add(vector, graph->vertex[start].name);
    
    return vector;

}

str_vector **get_connections(graph_t *graph) {
    str_vector **vectors = calloc(1,sizeof(str_vector));
    vectors[0] = 0;
    int *used = calloc(graph->size, sizeof(int));
    for (int i = 0; i < graph->size; i++) {
        if (used[i] == 0) {
            used[i] = 1;
            int flag = 0;
            for (int j = graph->size - 1; j>=0; j--) {
                int *visited = calloc(graph->size, sizeof(int));
                str_vector *res = dfs(graph, i, j, visited);
                if (res) {
                    str_vector_add(res, graph->vertex[i].name);
                    for (int i = 0; i < res->size; i++) {
                        int k = 0;
                        while (strcmp(graph->vertex[k].name, res->strings[i])!=0)
                            k += 1;
                        used[k] = 1;
                    }
                    free(visited);
                    int size = (int)vectors[0];
                    size += 1;
                    vectors = realloc(vectors, sizeof(str_vector*)*(size+1));
                    vectors[size] = res;
                    vectors[0] = size;
                    flag = 1;
                    
                    break;
                }
                free(visited);
            }
            if (!flag) {
                str_vector *tmp = malloc(sizeof(str_vector));
                str_vector_init(tmp);
                str_vector_add(tmp, graph->vertex[i].name);
                int size = (int)vectors[0];
                size += 1;
                vectors = realloc(vectors, sizeof(str_vector*)*(size+1));
                vectors[size] = tmp;
                vectors[0] = size;
            }
            
        }
    }
    free(used);
    return vectors;
}
