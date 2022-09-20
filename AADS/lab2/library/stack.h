#ifndef STACK_H
#define STACK_H

typedef struct stack {  
    void *top;
} stack_t;

void stack_init(stack_t *stack);
void stack_push(stack_t *stack, char data);
void stack_print(stack_t *stack);
void stack_free(stack_t *stack);
char stack_peek(stack_t *stack);
int stack_is_empty(stack_t *stack);
char stack_pop(stack_t *stack);

#endif