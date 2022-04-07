#include <stdio.h>
#include <malloc.h>
#include "app.h"


void (*controller[12])(Table*) = {NULL, add_element, search_by_keys, search_in_ks1,\
    search_in_ks2, delete_by_keys, delete_in_ks1, delete_in_ks2, delete_version_in_ks1,\
    reorganise_ks1, new_table_from_kp2, print_table};

app_t *app_create() {
    app_t *app = (app_t*)malloc(sizeof(app_t));
    create_table(&app->table);
    return app;
}

void app_start(app_t *app) {
    int choice = -1;
    while(choice) {
        choice = dialog();
        if (choice == 0)
            return;
        controller[choice](app->table);
    }
    return;  
}

void app_finish(app_t *app) {
    //мб вьюшку сюда запилить
    printf("POKAPOKAPOKA!\n");
    table_free(app->table);
    free(app);
}
