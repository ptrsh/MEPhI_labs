#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "string_vector.h"
#include "vector.h"

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

void print_graph(graph_t *graph) {
    for (int i = 0; i<graph->size; i++)
        printf("Вершина #%d\nИмя: %s\nx: %f\ny: %f\n\n", i, graph->vertex[i].name,\
                                            graph->vertex[i].x, graph->vertex[i].y);
}

void print_matrix(graph_t *graph) {
    for (int i = 0; i<graph->size; i++){
        for (int j = 0; j<graph->size; j++)
            printf("%6.1f ", graph->matrix[i][j]);
        printf("\n\n");
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
            //free(graph->vertex[graph->size].name);
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
        //free(graph->vertex[i].name);
    }
    free(graph->vertex);
    free(graph->matrix);
    free(graph);
}

void draw_graph(graph_t *this) {
    FILE *file = fopen("graph.dot", "w");
    fprintf(file, "strict graph { node [style=filled] ");
    int used[this->size];
    for (int u = 0; u < this->size; u++) {
        for (int v = 0; v < this->size; v++) {
            if (this->matrix[u][v] == 0) continue;
            used[u] = 1;
            used[v] = 1;

            fprintf(file, "\"%s\" -- \"%s\" [label=%.2f] ", this->vertex[u].name, this->vertex[v].name, this->matrix[u][v]);
        }
    }
    for (int i = 0; i < this->size; i++)
        if (used[i] == 0) fprintf(file, "\"%s\" ", this->vertex[i].name);
    fprintf(file, "}");
    fclose(file);
    system("dot graph.dot -Tpng -o graph.png");
    printf("The graph is drawn in the graph.png\n");
}

vector_t *dfs(graph_t *this, int start, int end, vector_t *visited) {
    if (this->matrix[start][end] != 0) return vector_init(1, end);

    visited->data[start] = 1;

    for (int i = 0; i < this->size; i++) {
        if (visited->data[i] == 1 || this->matrix[start][i] == 0) continue;
        vector_t *res = dfs(this, i, end, visited);
        if (res != NULL) return vector_push(res, i);;
    }

    return NULL;
}

vector_t *dfs_sort(graph_t *this, int start, vector_t *visited) {
    vector_t *order = vector_init(0, 0);
    visited->data[start] = 1;
    for (int i = 0; i < this->size; i++) {
        if (this->matrix[start][i] == 0 || visited->data[i] == 1) continue;
        vector_merge(order, dfs_sort(this, i, visited));
    }
    return vector_push(order, start);
}

vector_t *dfs_connections(graph_t *this, int start, vector_t *visited) {
    visited->data[start] = 1;
    vector_t *res = vector_init(1, start);
    for (int i = 0; i < this->size; i++) {
        if (this->matrix[start][i] == 0 || visited->data[i] == 1) continue;
        vector_merge(res, dfs_connections(this, i, visited));
    }
    return res;
}

str_vector **get_connections(graph_t *this) {
    str_vector **vectors = calloc(1,sizeof(str_vector));
    vectors[0] = 0;
    
    vector_t *visited = vector_init(this->size, 0);
    vector_t *order = vector_init(0, 0);

    for (int i = 0; i < this->size; i++)
        if (visited->data[i] == 0) vector_merge(order, dfs_sort(this, i, visited));
    for (int i = 0; i < visited->size; i++) visited->data[i] = 0;
    for (int i = 0; i < order->size; i++) {
        if (visited->data[order->data[i]] == 1) continue;
        vector_t *connectivity = dfs_connections(this, order->data[i], visited);
        str_vector *tmp = malloc(sizeof(str_vector));
        str_vector_init(tmp);
        for (int i = 0; i<connectivity->size; i++) {
            str_vector_add(tmp, this->vertex[connectivity->data[i]].name);
        }
        int size = (int)vectors[0];
        size += 1;
        vectors = realloc(vectors, sizeof(str_vector*)*(size+1));
        vectors[size] = tmp;
        vectors[0] = size;

        //str_vector_print(tmp);
        vector_free(connectivity);
        
    }
    
    vector_free(visited);
    vector_free(order);
    return vectors;

}

str_vector *get_dfs(graph_t *graph, char *name1, char *name2) {
    str_vector *vector = malloc(sizeof(str_vector));
    str_vector_init(vector);
    int start;
    int end;
    get_position(graph, name1, name2, &start, &end);
    vector_t *visited = vector_init(graph->size, 0);
    vector_t *res = dfs(graph, start, end, visited);
    vector_free(visited);
    res = vector_push(res, start);
    for (int i = 0; i < res->size; i++)
        str_vector_add(vector, graph->vertex[res->data[i]].name);
    vector_free(res);
    return vector;
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

/*
int main() {
    
    graph_t *graph = malloc(sizeof(graph_t));
    graph->size = 0;
    graph->vertex = malloc(sizeof(vertex_t));
    graph->matrix = malloc(sizeof(double *));
    
    
    add_vertex(graph, "kek", 10.0, 20.0);
    add_vertex(graph, "lol", 20.0, 10.0);
    add_vertex(graph, "keklol", 110.0, 7.0);
    add_vertex(graph, "keklolarbidol", 1.0, 2.0);
    add_vertex(graph, "pp", 11.0, 22.0);
    add_vertex(graph, "rp", 11.0, 2.0);
    add_vertex(graph, "dd", 1.0, 22.0);
    add_vertex(graph, "am", 1.0, 22.0);
    add_vertex(graph, "amr", 11.0, 22.0);

    add_edge(graph, "kek", "lol");
    add_edge(graph, "kek", "keklol");
    add_edge(graph, "kek", "keklolarbidol");
    add_edge(graph, "keklol", "keklolarbidol");
    add_edge(graph, "lol", "keklolarbidol");
    add_edge(graph, "lol", "keklol");
    add_edge(graph, "dd", "pp");
    //add_edge(graph, "dd", "keklolarbidol");
    add_edge(graph, "rp", "pp");
    add_edge(graph, "dd", "pp");
    add_edge(graph, "dd", "rp");
    add_edge(graph, "kek", "rp");
    add_edge(graph, "am", "amr");

    //draw_graph(graph);


    str_vector **res = get_connections(graph);
    for (int i = 1; i<=(int)res[0]; i++) {
        str_vector_print(res[i]);
        str_vector_free(res[i]);
    }

    free(res);

    free_graph(graph);
    
    
}

*/