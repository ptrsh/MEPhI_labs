#include "stdio.h"
#include "../other/readline.h"
#include "item_view.h"


void print_item(Item *this) {
    do {
        printf("[ %s | v.%d ] -> ", this->info, this->version);
        this = item_get_next(this);
    } while (this != NULL);
    printf("(null)\n");
}