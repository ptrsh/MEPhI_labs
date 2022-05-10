#include "stdio.h"
#include "stdlib.h"

#include "../models/table.h"
#include "table_helper.h"

Table *file_load_table(unsigned long ptr) {
    Table *table = malloc(sizeof(Table));
    FILE *file = fopen(FILENAME, MODE);
    int size = 0;
    fseek(file, ptr, SEEK_SET);
    fread(&size, sizeof(size), 1, file);
    fclose(file);
    table->keySpace1 = ptr;
    table->keySpace2 = ptr + sizeof(size_t) * 2 + sizeof(unsigned long) * size;
    return table;
}

int file_check_table() {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    int res = ftell(file) > 1;
    fclose(file);
    return res;
}
