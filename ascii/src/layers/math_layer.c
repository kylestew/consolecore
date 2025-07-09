#include "layers/math_layer.h"

#include <math.h>
#include <stdlib.h>

typedef struct {
    // function signature for math-based visual functions
    // typedef float (*MathFunc)(float x, float y, float t);
    MathFunc func;
    float scale;
    float speed;
    float time;
} MathLayerData;

void math_layer_update(void *self, float dt) {
    MathLayerData *data = (MathLayerData *) self;
    data->time += dt * data->speed;
}

void math_layer_process(void *self, Cell *buffer, int w, int h, float aspect) {
    MathLayerData *data = (MathLayerData *) self;
    // float aspect        = (float) w / (float) h;
    float scale = data->scale;
    float t     = data->time;

    for (int y = 0; y < h; ++y) {
        float ny = (2.0f * y / h - 1.0); // normalize to [-1, 1]
        for (int x = 0; x < w; ++x) {
            float nx  = (2.0f * x / w - 1.0f) / aspect;
            float val = data->func(nx * scale, ny * scale, t);

            buffer[y * w + x].value = fmaxf(0.0f, fminf(val, 1.0f));
        }
    }
}

Layer *create_math_layer(MathFunc func, float scale, float speed) {
    MathLayerData *data = malloc(sizeof(MathLayerData));
    data->func          = func;
    data->scale         = scale;
    data->speed         = speed;
    data->time          = 0.0f;

    Layer *layer   = malloc(sizeof(Layer));
    layer->process = math_layer_process;
    layer->update  = math_layer_update;
    layer->data    = data;
    layer->blend   = BLEND_REPLACE; // default, caller can override
    layer->name    = "Math";

    return layer;
}

void destroy_math_layer(Layer *layer) {
    free(layer->data);
    free(layer);
}

float math_func_sine_rings(float x, float y, float t) {
    float r2 = x * x + y * y;
    return 0.5f + 0.5f * sinf(r2 * 10.0f - t);
}

float math_func_wave_interference(float x, float y, float t) {
    float v1 = sinf(10.0f * (x + t));
    float v2 = sinf(10.0f * (y - t));
    float v3 = sinf(10.0f * (x * cosf(t) + y * sinf(t)));

    return 0.5f + 0.5f * (v1 + v2 + v3) / 3.0f;
}

float math_func_spiral(float x, float y, float t) {
    float r     = sqrtf(x * x + y * y);
    float angle = atan2f(y, x);
    return 0.5f + 0.5f * sinf(10.0f * r - 5.0f * angle - t);
}

float math_func_checker(float x, float y, float t) {
    int xi    = (int) (floorf(x * 5.0f));
    int yi    = (int) (floorf(y * 5.0f));
    int check = (xi + yi) % 2;
    return 0.5f + 0.5f * sinf(t * 5.0f + check * 3.1415f);
}
