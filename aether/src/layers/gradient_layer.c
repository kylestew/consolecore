#include "gradient_layer.h"

#include <math.h>
#include <stdlib.h>

typedef struct {
    u_int32_t color0;    // start color
    u_int32_t color1;    // end color
    float angle_radians; // 0 = left->right, PI/2 = top->bottom
} GradientLayerData;

static inline u_int8_t lerp_u8(u_int8_t a, u_int8_t b, float t) { return (u_int8_t) (a + (b - a) * t); }

void gradient_process(void *self, u_int32_t *buffer, u_int32_t *in_buffer, int w, int h) {
    (void) in_buffer;

    GradientLayerData *data = (GradientLayerData *) self;

    float cx = w / 2.0f;
    float cy = h / 2.0f;

    float dx = cosf(data->angle_radians);
    float dy = sinf(data->angle_radians);

    float half_diag = sqrtf(w * w + h * h) / 2.0f;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float relx = x - cx;
            float rely = y - cy;

            float t = (relx * dx + rely * dy) / half_diag; // project onto direction
            t       = (t + 1.0f) * 0.5f;                   // map from [-1,1] → [0,1]

            if (t < 0.0f)
                t = 0.0f;
            if (t > 1.0f)
                t = 1.0f;

            // break up start/end color into their components for interp
            u_int8_t r0 = (data->color0 >> 16) & 0xFF;
            u_int8_t g0 = (data->color0 >> 8) & 0xFF;
            u_int8_t b0 = data->color0 & 0xFF;
            u_int8_t r1 = (data->color1 >> 16) & 0xFF;
            u_int8_t g1 = (data->color1 >> 8) & 0xFF;
            u_int8_t b1 = data->color1 & 0xFF;

            uint8_t r = lerp_u8(r0, r1, t);
            uint8_t g = lerp_u8(g0, g1, t);
            uint8_t b = lerp_u8(b0, b1, t);

            buffer[y * w + x] = (0xFFu << 24) | (r << 16) | (g << 8) | b;
        }
    }
}

Layer *create_gradient_layer(u_int32_t color0, u_int32_t color1, float angle_radians) {
    GradientLayerData *data = malloc(sizeof(GradientLayerData));
    if (!data) {
        return NULL;
    }

    data->color0        = color0;
    data->color1        = color1;
    data->angle_radians = angle_radians;

    Layer *layer = malloc(sizeof(Layer));
    if (!layer) {
        free(data);
        return NULL;
    }
    layer->process = gradient_process;
    layer->data    = data;

    return layer;
}
