#include "invert_layer.h"

#include <stdlib.h>
#include <sys/_types/_u_int32_t.h>
#include <sys/_types/_u_int8_t.h>

void invert_process(void *self, u_int32_t *buffer, u_int32_t *in_buffer, int w, int h) {
    (void) self;

    for (int i = 0; i < w * h; i++) {
        u_int32_t color = in_buffer[i];

        u_int8_t a = (color >> 24) & 0xFF;
        u_int8_t r = (color >> 16) & 0xFF;
        u_int8_t g = (color >> 8) & 0xFF;
        u_int8_t b = color & 0xFF;

        r = 255 - r;
        g = 255 - g;
        b = 255 - b;

        buffer[i] = (a << 24) | (r << 16) | (g << 8) | b;
    }
}

Layer *create_invert_layer() {
    Layer *layer = malloc(sizeof(Layer));
    if (!layer) {
        return NULL;
    }
    layer->process = invert_process;
    layer->data    = NULL;

    return layer;
}
