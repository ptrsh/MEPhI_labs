#ifndef STR_H
#define STR_H

typedef struct str {
    int length;
    char *text;
} str_t;

void str_init(str_t *str);
void str_add(str_t *str, char text);
void str_print(str_t *str);
void str_get(str_t *str);
void str_free(str_t *str);
#endif