#include "../other/item_helper.h"
#include "../views/errors.h"
#include "../views/table_view.h"
#include "../views/item_view.h"
#include "table_controller.h"

void add_element(Table *table) {
    unsigned long ptr = read_element();
    Item *item = file_load_item(ptr);
    Item *tmp;
    if (table_keypair_found(table, &tmp, item->key1, item->key2) == 1)
        item_add(tmp, ptr);
    else if (table_enough_space(table) == 1)
        table_add(table, ptr);
    else
        insert_error();
    item_free(item);
}

void search_by_keys(Table *table) {
    char *key1, *key2;
    read_keys(&key1, &key2);
    Item *item;
    if (table_keypair_found(table, &item, key1, key2) == 0) {
        find_error();
    } else {
        item = file_load_item(item);
        print_item(item);
    }
    free(key1);
    free(key2);
}

void search_in_ks1(Table *table) {
    char *key;
    read_key(&key);
    Item *item;
    if (table_keypair_found_ks1(table, &item, key) == 0) {
        find_error();
    } else {
        item = file_load_item(item);
        print_item(item);
    }
    free(key);
}

void search_in_ks2(Table *table) {
    char *key;
    read_key(&key);
    Item *item;
    if (table_keypair_found_ks2(table, &item, key) == 0) {
        find_error();
    } else {
        item = file_load_item(item);
        print_item(item);
    }
    free(key);
}

void delete_by_keys(Table *table) {
    char *key1, *key2;
    read_keys(&key1, &key2);
    table_delete_by_keys(table, key1, key2);
    free(key1);
    free(key2);
}

void delete_in_ks1(Table *table) {
    char *key;
    read_key(&key);
    table_delete_by_key1(table, key);
    free(key);
}

void delete_in_ks2(Table *table) {
    char *key;
    read_key(&key);
    table_delete_by_key2(table, key);
    free(key);
}

void reorganise_ks2(Table *table) {
    table_reorganise(table);
}

void new_table_from_kp2(Table *table) {
    return;
}
void print_table(Table *table) {
    table_print(table);
}