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

int check(char *s) {
    for (int i = 0; i < strlen(s); i++) {
        if (((s[i] > '9') || (s[i] < '0'))&&(s[i]!='.'))
            return 0;
    }
    return 1;
}

int read_num(char *error_msg, int min, int max) {
    do {
        char *s = get_str();
        if (check(s)) {
            int num  = atof(s);
            if ((num>=min)&&(num<=max)) {
                free(s);
                return num;
            }
        }
        printf("%s\n", error_msg);
        free(s);
    } while (1);
}


