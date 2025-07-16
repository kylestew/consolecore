#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "layer.h"

typedef struct {
    Layer **items;
    int count;
    int capacity;
} LayerStack;

void layer_stack_init(LayerStack *stack);
void layer_stack_push(LayerStack *stack, Layer *layer);
void layer_stack_free(LayerStack *stack);

#endif // LAYER_STACK_H
