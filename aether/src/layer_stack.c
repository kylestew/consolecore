#include "layer_stack.h"

#include <stdlib.h>

void layer_stack_init(LayerStack *stack) {
    stack->count    = 0;
    stack->capacity = 4;
    stack->items    = malloc(sizeof(Layer *) * stack->capacity);
}

void layer_stack_push(LayerStack *stack, Layer *layer) {
    if (stack->count == stack->capacity) {
        stack->capacity *= 2;
        stack->items = realloc(stack->items, sizeof(Layer *) * stack->capacity);
    }
    stack->items[stack->count++] = layer;
}

void layer_stack_free(LayerStack *stack) {
    for (int i = 0; i < stack->count; i++) {
        Layer *layer = stack->items[i];
        if (layer) {
            free(layer->data);
            free(layer);
        }
    }
    free(stack->items);
    stack->items    = NULL;
    stack->count    = 0;
    stack->capacity = 0;
}
