#include "controllers/table_controller.h"
#include "views/dialog.h"
#include "other/readline.h"

#ifndef APP_H
#define APP_H

typedef struct app {
    Table *table;
} app_t;


app_t *app_create();
void app_start(app_t *app);
void app_finish(app_t *app);

#endif