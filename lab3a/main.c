#include <stdio.h>
#include <malloc.h>
#include "models/main.h"

int main() {
    Table* table = table_init(10, 10);
    table_add(table, "111", "aaa", "ggg");
    table_add(table, "222", "aaa", "bbb");
    table_add(table, "333", "kkk", "ttt");
    table_add(table, "444", "aaa", "ttt");
    table_add(table, "555", "aaa", "ttt");
    table_add(table, "555", "aaa", "ppp");
    table_free(table);
    return 0;
}