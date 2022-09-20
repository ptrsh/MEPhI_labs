#include "models/table.h"
#include "views/table_view.h"

#ifndef APPLICATION_H
#define APPLICATION_H

typedef struct app {
    Table *table;
} app_t;

app_t *app_create();
void app_start(app_t *app);
void app_finish(app_t *app);

#endif 
