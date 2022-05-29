#include <stdio.h>
#include <malloc.h>
#include "app.h"


void (*controller[8])(node_t*) = {NULL, add_element, search_by_key,\
    special_search_by_key, delete_by_key, traversal, print, timing};

app_t *app_create() {
    app_t *app = (app_t*)malloc(sizeof(app_t));
    init_tree(&app->tree);
    return app;
}

void app_start(app_t *app) {
    int choice = -1;
    while(choice) {
        choice = dialog();
        if (choice == 0)
            return;
        else if (choice == 8) {
            free_tree(app->tree);
            app->tree = load_from_file();
        }
        else 
            controller[choice](app->tree);
    }
    return;  
}

void app_finish(app_t *app) {
    free_tree(app->tree);
    free(app);
}
