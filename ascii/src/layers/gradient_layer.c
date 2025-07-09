#include "layers/gradient_layer.h"

#include <stdlib.h>

typedef struct {
    // internal data for layer use
} GradientLayerData;

void gradient_process(void *self, Cell *buffer, int w, int h, float aspect) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float value             = (float) x / (float) (w);
            buffer[y * w + x].value = value;
        }
    }
}

Layer *create_gradient_layer() {
    GradientLayerData *data = malloc(sizeof(GradientLayerData));
    Layer *layer            = malloc(sizeof(Layer));
    layer->process          = gradient_process;
    layer->data             = data;
    return layer;
}

void destroy_gradient_layer(Layer *layer) {
    free(layer->data);
    free(layer);
}
