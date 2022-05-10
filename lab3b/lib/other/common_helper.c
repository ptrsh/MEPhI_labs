#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "common_helper.h"

void init_file() {
    FILE *file = fopen(FILENAME, "ab+");
    fclose(file);
}

unsigned long file_add_string(char *str) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    unsigned long ptr = ftell(file);
    char len = (char)strlen(str);
    fwrite(&len, sizeof(char), 1, file);
    fwrite(str, sizeof(char), strlen(str), file);
    fclose(file);
    return ptr;
}

char *file_load_string(unsigned long ptr) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long)ptr, SEEK_SET);
    char len = (char)fgetc(file);
    char *str = calloc(len + 1, sizeof(char));
    fread(str, sizeof(char), len, file);
    fclose(file);
    return str;
}