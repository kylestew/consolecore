#include "layers/noise_layer.h"

#include <stdlib.h>
#include <time.h>

typedef struct {
    float intensity; // controls how bright the noise is
} NoiseLayerData;

void noise_process(void *self, Cell *buffer, int w, int h, float aspect) {
    (void) aspect;

    NoiseLayerData *data = (NoiseLayerData *) self;
    for (int i = 0; i < w * h; ++i) {
        float r         = (float) rand() / (float) RAND_MAX; // random 0-1
        buffer[i].value = r * data->intensity;
    }
}

Layer *create_noise_layer(float intensity) {
    // Seed rand if not already done globally
    // static int seeded = 0;
    // if (!seeded) {
    srand((unsigned int) time(NULL));
    // seeded = 1;
    // }

    NoiseLayerData *data = malloc(sizeof(NoiseLayerData));
    data->intensity      = intensity; // full noise

    Layer *layer   = malloc(sizeof(Layer));
    layer->process = noise_process;
    layer->update  = NULL;
    layer->data    = data;
    return layer;
}

void destroy_noise_layer(Layer *layer) {
    free(layer->data);
    free(layer);
}
