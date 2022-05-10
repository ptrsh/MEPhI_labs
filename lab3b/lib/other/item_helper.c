#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "item_helper.h"

unsigned long file_add_item(Item *item) {
    unsigned long ptr = file_add_string(item->info);
    file_add_string(item->key1);
    file_add_string(item->key2);
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    fwrite(&item->version, sizeof(item->version), 1, file);
    fwrite(&item->next, sizeof(unsigned long), 1, file);
    fclose(file);
    return ptr;
}

Item *file_load_item(unsigned long ptr) {
    Item *item = malloc(sizeof(Item));
    item->info = file_load_string(ptr);
    ptr += strlen(item->info) + 1;
    item->key1 = file_load_string(ptr);
    ptr += strlen(item->key1) + 1;
    item->key2 = file_load_string(ptr);
    ptr += strlen(item->key2) + 1;
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, ptr, SEEK_SET);
    fread(&item->version, sizeof(item->version), 1, file);
    fread(&item->next, sizeof(item->next), 1, file);
    fclose(file);
    return item;
}

void file_update_item(Item *item, unsigned long ptr) {
    ptr += strlen(item->info) + 1;
    ptr += strlen(item->key1) + 1;
    ptr += strlen(item->key2) + 1;
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, ptr, SEEK_SET);
    fwrite(&item->version, sizeof(item->version), 1, file);
    fwrite(&item->next, sizeof(item->next), 1, file);
    fclose(file);
}
