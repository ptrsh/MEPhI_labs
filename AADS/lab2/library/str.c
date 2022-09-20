#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "str.h"

void str_init(str_t *str) {
    str->length = 0;
    str->text = (char*)malloc(sizeof(char));
}

void str_add(str_t *str, char text) {
    str->length += 1;
    str->text = (char*)realloc(str->text, str->length * sizeof(char*));
    (str->text)[str -> length - 1] = text;
}

void str_print(str_t *str) {
    for (int i = 0; i < str->length; ++i)
        printf("%c", (str->text)[i]);
    printf("\n");
}


void str_get(str_t *str) {
    str->length = 0;
    str->text = realloc(str->text, 0);
    char buf[81] = {0};
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (str->length == 0) {
                return;
        }
    } else if (n > 0){
        int chunk_len = strlen(buf);
        int str_len = str->length + chunk_len;
        str->text = realloc(str->text, str_len + 1);
        memcpy(str->text + str->length, buf, chunk_len);
        str->length = str_len;
    } else
        scanf("%*c");
    
    } while (n>0);
    if (str->length > 0)
        str->text[str->length] = '\0';
    else 
        str->text = calloc(1, sizeof(char));
}


void str_free(str_t *str) {
    free(str->text);
}
