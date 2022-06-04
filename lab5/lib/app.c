#include <stdio.h>
#include <malloc.h>
#include "app.h"


void (*controller[11])(graph_t*) = {NULL, vertex_add, edge_add, vertex_delete,\
    edge_delete, shortest_path_find, go_dfs, components_get, matrix_print,\
    graph_draw, load_city};

app_t *app_create() {
    app_t *app = (app_t*)malloc(sizeof(app_t));
    app->graph = init_graph();
    return app;
}

void app_start(app_t *app) {
    int choice = -1;
    while(choice) {
        choice = dialog();
        printf("%d\n", choice);
        if (choice == 0)
            return;
        controller[choice](app->graph);
    }
    return;  
}

void app_finish(app_t *app) {
    free_graph(app->graph);
    free(app);
}
