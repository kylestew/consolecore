#ifndef LAYER_H
#define LAYER_H

#include "blend_modes.h"

#include <stdlib.h>

typedef struct {
    void (*process)(void *self, u_int32_t *out_buffer, u_int32_t *in_buffer, int width, int height);

    // pixel data before converting to an SDL texture on the final output
    u_int32_t *color_buffer;
    int width, height;
    BlendMode blend;
    const char *name;

    // custom data space for given layer to attach and we send back this to the process on each frame
    void *data;
} Layer;

#endif
