#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "loader_tools.h"

void fileInit() {
    FILE *file = fopen(FILENAME, "ab+");
    fclose(file);
}

offset fileStringAppend(char *str) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    char len = (char)strlen(str);
    fwrite(&len, sizeof(char), 1, file);
    fwrite(str, sizeof(char), strlen(str), file);
    fclose(file);
    return ptr;
}

char *fileStringLoad(offset ptr) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long)ptr, SEEK_SET);
    char len = (char)fgetc(file);
    char *str = calloc(len + 1, sizeof(char));
    fread(str, sizeof(char), len, file);
    fclose(file);
    return str;
}
