#include <stdio.h>
#include <malloc.h>
#include "table_controller.h"

void create_table(Table **table) {
    int ks1_size, ks2_size;
    read_table_size(&ks1_size, &ks2_size);
    *table = table_init(ks1_size, ks2_size);
}

void add_element(Table *table) {
    char *data, *key1, *key2; 
    read_element(&data, &key1, &key2);
    int result = table_add(table, data, key1, key2);
    check_add(result);
}

void search_by_keys(Table *table) {
    char *key1, *key2;
    read_keys(&key1, &key2);
    Item *item = table_search_by_keys(table, key1, key2);
    print_item(item);
    free(key1);
    free(key2);
}

void search_in_ks1(Table *table) {
    char *key;
    read_key(&key);
    Key *keys = table_search_in_ks1(table, key);
    print_key(keys);
    free(key);
}

void search_in_ks2(Table *table) {
    char *key;
    read_key(&key);
    Key *keys = table_search_in_ks2(table, key);
    print_key(keys);
    free(key);
}


void delete_by_keys(Table *table) {
    char *key1, *key2;
    read_keys(&key1, &key2);
    int result = table_delete_by_keys(table, key1, key2);
    check_delete(result);
    free(key1);
    free(key2);
}

void delete_in_ks1(Table *table) {
    char *key;
    read_key(&key);
    int result = table_delete_in_ks1(table, key);
    check_delete(result);
    free(key);
}

void delete_in_ks2(Table *table) {
    char *key;
    read_key(&key);
    int result = table_delete_in_ks2(table, key);
    check_delete(result);
    free(key);
} 

void delete_version_in_ks1(Table *table) {
    char *key;
    int version;
    read_key_version(&key, &version);
    int result = table_delete_version_in_ks1(table, key, version);
    check_delete(result);
    free(key);
}

void reorganise_ks1(Table *table) {
    table_reorganise_ks1(table);
}

void new_table_from_kp2(Table *table) {
    char *key;
    read_key(&key);
    Table *new_table = table_new_from_kp2(table, key);
    print_table(new_table);
    table_free(new_table);
    free(key);
}

void print_table(Table *table) {
    printf("Первое пространство:\n");
    print_keyspace(table->ks1, table->ks1_size);
    printf("Второе пространство:\n");
    print_keyspace(table->ks2, table->ks2_size);
}

