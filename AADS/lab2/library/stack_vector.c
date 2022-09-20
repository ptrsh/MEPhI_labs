#include <stdio.h>
#include <malloc.h>
#include "vector.h"
#include "stack.h"

void stack_init(stack_t *stack) {
    stack->top = (vector_t*)malloc(sizeof(vector_t));
    vector_init(stack->top);
}

void stack_push(stack_t *stack, char data) {
    vector_push(stack->top, data);
}

void stack_print(stack_t *stack) {
    vector_print(stack->top);
}

void stack_free(stack_t *stack) {
    vector_free(stack->top);
    free(stack->top);
}

char stack_peek(stack_t *stack) {
    return vector_peek(stack->top);
}

int stack_is_empty(stack_t *stack) {
    return vector_is_empty(stack->top);
}

char stack_pop(stack_t *stack) {
    return vector_pop(stack->top);
}