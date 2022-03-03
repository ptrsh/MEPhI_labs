#include <stdio.h>
#include "library/stack.h"
#include <malloc.h>
#include <string.h>

char *get_str();
int priority(char ch);
int is_var(char ch);
void infix_to_postfix(char *str);

int main(){
    printf("Введите инфиксную нотацию:\n");
    char *input = get_str();
    infix_to_postfix(input);
    free(input);
    return 0;
}

char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
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

int priority(char ch) {
    switch(ch) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
}

int is_var(char ch) {
    return ((ch >= 'a') && (ch <= 'z') || (ch >= 'A') && (ch <= 'Z'));
}

void infix_to_postfix(char *str) {
    stack_t stack;
    stack_init(&stack);
    char x;
    printf("[Output] ");
    for (int i = 0; str[i] != '\0'; ++i) {
        if (is_var(str[i]))
            printf("%c", str[i]);
        else if (str[i] == '(')
            stack_push(&stack, str[i]);
        else if (str[i] == ')') {
            while((x = stack_pop(&stack)) != '(')
                printf("%c", x);
        }
        else {
            while (priority(stack_peek(&stack))>=priority(str[i]))
                printf("%c", stack_pop(&stack));
            stack_push(&stack, str[i]);
        }
    }
   
    while(!stack_is_empty(&stack))
        printf("%c", stack_pop(&stack));
    
    printf("\n");
    stack_free(&stack);
}
