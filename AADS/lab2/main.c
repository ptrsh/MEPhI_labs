#include <stdio.h>
#include "library/stack.h"
#include "library/str.h"
#include <malloc.h>

int priority(char ch);
int is_var(char ch);
void infix_to_postfix(char *str);

int main(){
    str_t input;
    str_init(&input);

    printf("Введите инфиксную нотацию:\n");
    str_get(&input);
    infix_to_postfix(input.text);

    str_free(&input);
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
        default:
            return -1;
    }
}

int is_var(char ch) {
    return ((ch >= 'a') && (ch <= 'z') || (ch >= 'A') && (ch <= 'Z'));
}

void infix_to_postfix(char *str) {
    stack_t stack;
    str_t postfix;
    stack_init(&stack);
    str_init(&postfix);
    char x;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (is_var(str[i]))
            str_add(&postfix, str[i]);
        else if (str[i] == '(')
            stack_push(&stack, str[i]);
        else if (str[i] == ')') {
            while(((x = stack_pop(&stack)) != '(') && (!stack_is_empty(&stack)))
                str_add(&postfix, x);
        }
        else {
            if (priority(str[i])== -1) {
                printf("Был введён некорректный оператор!\n");
                stack_free(&stack);
                str_free(&postfix);
                return;
            }
            while (priority(stack_peek(&stack))>=priority(str[i]))
                str_add(&postfix, stack_pop(&stack));
            stack_push(&stack, str[i]);
        }
    }
    while(!stack_is_empty(&stack))
        str_add(&postfix, stack_pop(&stack));
    
    printf("Постфиксная нотация:\n");
    str_print(&postfix);

    stack_free(&stack);
    str_free(&postfix);
}
