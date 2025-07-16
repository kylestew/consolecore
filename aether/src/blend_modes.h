#ifndef BLEND_MODES_H
#define BLEND_MODES_H

#include <stdlib.h>

typedef enum {
    BLEND_REPLACE, // default
    BLEND_ADD,
    BLEND_MULTIPLY,
    BLEND_MAX
} BlendMode;

u_int32_t blend_colors(u_int32_t dst, u_int32_t src, BlendMode mode);

#endif
