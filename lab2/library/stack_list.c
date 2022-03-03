#include <stdio.h>
#include <malloc.h>
#include "list.h"
#include "stack.h"

void stack_init(stack_t *stack) {
    stack->top = (list_t*)malloc(sizeof(list_t));
    list_init(stack->top);
}

void stack_push(stack_t *stack, char data) {
    list_push_front(stack->top, data);
}

void stack_print(stack_t *stack) {
    list_print(stack->top);
}

void stack_free(stack_t *stack) {
    list_free(stack->top);
    free(stack->top);
}

char stack_peek(stack_t *stack) {
    return list_peek(stack->top);
}

int stack_is_empty(stack_t *stack) {
    return list_is_empty(stack->top);
}

char stack_pop(stack_t *stack) {
    return list_pop(stack->top);
}