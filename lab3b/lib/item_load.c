#include "stdio.h"
#include "stdlib.h"
#include "string.h"


offset fileItemAppend(Item *item) {
    offset ptr = fileStringAppend(item->content);
    fileStringAppend(item->key1);
    fileStringAppend(item->key2);
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    fwrite(&item->version, sizeof(item->version), 1, file);
    fwrite(&item->next, sizeof(offset), 1, file);
    fclose(file);
    return ptr;
}

Item *fileItemLoad(offset ptr) {
    Item *item = malloc(sizeof(Item));
    item->content = fileStringLoad(ptr);
    ptr += strlen(item->content) + 1;
    item->key1 = fileStringLoad(ptr);
    ptr += strlen(item->key1) + 1;
    item->key2 = fileStringLoad(ptr);
    ptr += strlen(item->key2) + 1;
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, ptr, SEEK_SET);
    fread(&item->version, sizeof(item->version), 1, file);
    fread(&item->next, sizeof(item->next), 1, file);
    fclose(file);
    return item;
}

void fileItemUpdate(Item *item, offset ptr) {
    ptr += strlen(item->content) + 1;
    ptr += strlen(item->key1) + 1;
    ptr += strlen(item->key2) + 1;
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, ptr, SEEK_SET);
    fwrite(&item->version, sizeof(item->version), 1, file);
    fwrite(&item->next, sizeof(item->next), 1, file);
    fclose(file);
}
