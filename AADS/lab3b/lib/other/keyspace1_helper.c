#include "stdio.h"
#include "keyspace1_helper.h"

unsigned long file_add_keyspace1(KeySpace1 *keySpace) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    unsigned long ptr = ftell(file);
    fwrite(&keySpace->size, sizeof(keySpace->size), 1, file);
    fwrite(&keySpace->used, sizeof(keySpace->used), 1, file);
    fwrite(keySpace->items, sizeof(unsigned long), keySpace->size, file);
    fclose(file);
    return ptr;
}

KeySpace1 *file_load_keyspace1(unsigned long ptr) {
    KeySpace1 *keySpace = malloc(sizeof(KeySpace1));
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&keySpace->size, sizeof(keySpace->size), 1, file);
    fread(&keySpace->used, sizeof(keySpace->used), 1, file);
    keySpace->items = calloc(keySpace->size, sizeof(unsigned long));
    fread(keySpace->items, sizeof(unsigned long), keySpace->size, file);
    fclose(file);
    return keySpace;
}

void file_update_keyspace1(KeySpace1 *keySpace, unsigned long ptr) {
    ptr += sizeof(keySpace->size);
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fwrite(&keySpace->used, sizeof(keySpace->used), 1, file);
    fwrite(keySpace->items, sizeof(unsigned long), keySpace->size, file);
    fclose(file);
}