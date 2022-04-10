#include "stdio.h"
#include "models/keyspaces.h"

offset fileKeySpaceAppend(KeySpace *keySpace) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    fwrite(&keySpace->size, sizeof(keySpace->size), 1, file);
    fwrite(&keySpace->used, sizeof(keySpace->used), 1, file);
    fwrite(keySpace->items, sizeof(offset), keySpace->size, file);
    fclose(file);
    return ptr;
}

KeySpace *fileKeySpaceLoad(offset ptr) {
    KeySpace *keySpace = malloc(sizeof(KeySpace1));
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&keySpace->size, sizeof(keySpace->size), 1, file);
    fread(&keySpace->used, sizeof(keySpace->used), 1, file);
    keySpace->items = calloc(keySpace->size, sizeof(offset));
    fread(keySpace->items, sizeof(offset), keySpace->size, file);
    fclose(file);
    return keySpace;
}
