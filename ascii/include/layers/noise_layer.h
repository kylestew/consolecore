#ifndef NOISE_LAYER_H
#define NOISE_LAYER_H

#include "layer.h"

Layer *create_noise_layer(float intensity);
void destroy_noise_layer(Layer * layer);

#endif
