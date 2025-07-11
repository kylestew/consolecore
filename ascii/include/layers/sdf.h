#ifndef SDF_LAYER_H
#define SDF_LAYER_H

#include "layer.h"

typedef enum {
    SDF_SHAPE_CIRCLE,
    SDF_SHAPE_BOX,
    SDF_SHAPE_LINE,
} SDFShape;

Layer *create_sdf_layer(SDFShape shape, float param1, float param2, float edge_thickness, float center_x,
                        float center_y);
void destroy_sdf_layer(Layer *layer);

#endif SDF_LAYER_H
