#include <stdio.h>
#include "library/stack.h"
#include <readline/readline.h>
#include <malloc.h>


int priority(char ch);
int is_var(char ch);
void infix_to_postfix(char *str);

int main(){
    printf("Введите инфиксную нотацию\n");
    char *input = readline("[Input] ");
    infix_to_postfix(input);
    free(input);
    return 0;
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
