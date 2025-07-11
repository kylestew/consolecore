#inclue "layers/sdf.h"

typedef struct {
    SDFShape shape;
    float param1; // radius or half-width
    float param2; // unused or half-height
    float edge_thickness;
    float center_x, center_y;
} SDFLayerData;

// Smoothstep helper
float smoothstep(float edge0, float edge1, float x) {
    float t = fminf(fmaxf((x - edge0) / (edge1 - edge0), 0.0f), 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

void sdf_process(void *self, Cell *buffer, int w, int h, float aspect) { SDFLayerData *data = (SDFLayerData *) self; }

Layer *create_sdf_layer(SDFShape shape, float param1, float param2, float edge_thickness, float center_x,
                        float center_y) {
    SDFLayerData *data   = malloc(sizeof(SDFLayerData));
    data->shape          = shape;
    data->param1         = param1;
    data->param2         = param2;
    data->edge_thickness = edge_thickness;
    data->center_x       = center_x;
    data->center_y       = center_y;

    Layer *layer   = malloc(sizeof(Layer));
    layer->process = sdf_process;
    layer->update  = NULL;
    layer->data    = data;
    return layer;
}

void destroy_sdf_layer(Layer *layer) {
    free(layer->data);
    free(layer);
}
