#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0){ 
            if (!res){
                return NULL;
        }
    } else if (n > 0){
        int chunk_len = strlen(buf);
        int str_len = len + chunk_len;
        res = realloc(res, str_len + 1);
        memcpy(res + len, buf, chunk_len);
        len = str_len;
    } else 
        scanf("%*c");
    
    } while (n>0);
    if (len > 0)
        res[len] = '\0';
    else 
        res = calloc(1, sizeof(char));
    return res;
    
}

char *get_str_file(FILE *file) {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n < 0){ 
            if (!res){
                return NULL;
        }
    } else if (n > 0){
        int chunk_len = strlen(buf);
        int str_len = len + chunk_len;
        res = realloc(res, str_len + 1);
        memcpy(res + len, buf, chunk_len);
        len = str_len;
    } else 
        fscanf(file, "%*c");
    
    } while (n>0);
    if (len > 0)
        res[len] = '\0';
    else 
        res = calloc(1, sizeof(char));
    return res;
    
}

int check(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if ((s[i] > '9') || (s[i] < '0'))
            return 0;
    }
    return 1;
}

int read_num(char *error_msg, int min, int max) {
    do {
        char *s = get_str();
        if (check(s)) {
            int num  = atoi(s);
            if ((num>=min)&&(num<=max)) {
                free(s);
                return num;
            }
        }
        printf("%s\n", error_msg);
        free(s);
    } while (1);
}

int parseInt(char *str, int *res) {
    *res = 0;
    int i = 0, sign = 1;

    if (strlen(str) < 1) return 0;

    if (str[0] == '0' && strlen(str) > 1) return 0;

    if (str[0] == '-') {
        if (strlen(str) < 2 || str[1] > '9' || str[1] <= '0')
            return 0;
        i = 1;
        sign = -1;
    }

    for (; i < strlen(str); i++) {
        if (str[i] > '9' || str[i] < '0')
            return 0;
        *res = *res * 10 + (str[i] - '0');
    }
    *res *= sign;

    return 1;
}



int read_large_num() {
    int success = 0, res = 0;
    while (!success) {
        char *str = get_str();
        success = parseInt(str, &res);
        if (!success)
            printf("Invalid input. Try again\n");
        free(str);
    }
    return res;
}


