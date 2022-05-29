#include <stdio.h>
#include "lib/app.h"

int main() {
    app_t *app = app_create();
    app_start(app);
    app_finish(app);
    return 0;
}