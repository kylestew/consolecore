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

static void blend_cell(Cell *dst, Cell src, BlendMode mode) {
    switch (mode) {
    case BLEND_REPLACE:
        dst->value = src.value;
        break;
    case BLEND_ADD:
        dst->value += src.value;
        break;
    case BLEND_MULTIPLY:
        dst->value *= src.value;
        break;
    case BLEND_MAX:
        if (src.value > dst->value)
            dst->value = src.value;
        break;
    }

    // Clamp to [0.0, 1.0]
    if (dst->value > 1.0f)
        dst->value = 1.0f;
    if (dst->value < 0.0f)
        dst->value = 0.0f;
}

void layer_stack_update_and_process(LayerStack *stack, Cell *buffer, int w, int h, float aspect, float dt) {
    // clear main output buffer
    for (int i = 0; i < w * h; ++i)
        buffer[i].value = 0.0f;

    Cell *temp = malloc(sizeof(Cell) * w * h);

    for (int i = 0; i < stack->count; ++i) {
        Layer *layer = stack->items[i];

        // optional update
        if (layer->update)
            layer->update(layer->data, dt);

        // clear temp buffer
        for (int j = 0; j < w * h; ++j)
            temp[j].value = 0.0f;

        // generate layer output into temp
        layer->process(layer->data, temp, w, h, aspect);

        // blend into main output buffer
        for (int j = 0; j < w * h; ++j)
            blend_cell(&buffer[j], temp[j], layer->blend);
    }

    free(temp);
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
