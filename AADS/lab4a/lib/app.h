#include "controllers/tree_controller.h"
#include "views/dialog.h"
#include "other/readline.h"
#include "models/node.h"

#ifndef APP_H
#define APP_H

typedef struct app {
    node_t *tree;
} app_t;


app_t *app_create();
void app_start(app_t *app);
void app_finish(app_t *app);

#endif