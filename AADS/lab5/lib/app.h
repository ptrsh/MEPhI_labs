#include "controllers/graph_controller.h"
#include "views/dialog.h"
#include "models/graph.h"
#include "other/readline.h"

#ifndef APP_H
#define APP_H

typedef struct app {
    graph_t *graph;
} app_t;


app_t *app_create();
void app_start(app_t *app);
void app_finish(app_t *app);

#endif