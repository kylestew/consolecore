#include "sdf_layer.h"

#include <math.h>
#include <stdlib.h>
#include <sys/_types/_u_int32_t.h>

typedef struct {
    SDFShape shape;
    float param1; // radius or half-width
    float param2; // unused or half-height
    float edge_thickness;
    float center_x, center_y;
} SDFLayerData;

void sdf_process(void *self, u_int32_t *color_buffer, u_int32_t *in_buffer, int width, int height) {
    (void) in_buffer;

    SDFLayerData *data = (SDFLayerData *) self;

    // normalize coordinates
    float scale;
    float x_offset = 0.0;
    float y_offset = 0.0;
    if (width > height) {
        scale    = 1.0 / height;
        x_offset = (width - height) / 2.0;
    } else {
        scale    = 1.0 / width;
        y_offset = (height - width) / 2.0;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float pX = (x - x_offset) * scale;
            float pY = (y - y_offset) * scale;

            float dx   = fabs(data->center_x - pX);
            float dy   = fabs(data->center_y - pY);
            float dist = sqrt(dx * dx + dy * dy);

            uint8_t r = 0;

            uint8_t g = 0;
            uint8_t b = 0;
            uint8_t a = 0;

            if (dist < data->param1) {
                r = 255;
                a = 255;
            }

            // // show edges
            // if (pX > 1.0) {
            //     b = 255.0;
            // }
            // if (pX < 0.0) {
            //     b = 128.0;
            // }

            color_buffer[y * width + x] = (a << 24) | (r << 16) | (g << 8) | b;
        }
    }
}

Layer *create_sdf_layer(SDFShape shape, float param1, float param2, float edge_thickness, float center_x,
                        float center_y) {
    SDFLayerData *data = malloc(sizeof(SDFLayerData));
    if (!data) {
        return NULL;
    }

    data->shape          = shape;
    data->param1         = param1;
    data->param2         = param2;
    data->edge_thickness = edge_thickness;
    data->center_x       = center_x;
    data->center_y       = center_y;

    Layer *layer = malloc(sizeof(Layer));
    if (!layer) {
        free(data);
        return NULL;
    }
    layer->process = sdf_process;
    layer->data    = data;

    return layer;
}
