#include "views/menu.h"
#include "other/table_helper.h"
#include "controllers/table_controller.h"
#include "app.h"

void (*controller[11])(Table*) = {NULL, add_element, search_by_keys, search_in_ks1,\
    search_in_ks2, delete_by_keys, delete_in_ks1, delete_in_ks2, reorganise_ks2,\
    new_table_from_kp2, print_table};

app_t *app_create() {
    app_t *app = malloc(sizeof(app_t));
    init_file();
    if (file_check_table() == 0)
        app->table = read_table_size();
    else
        app->table = file_load_table(0);
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
    table_free(app->table);
    free(app);
}

