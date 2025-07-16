#include "blend_modes.h"
#include "display.h"
#include "layer.h"
#include "layer_stack.h"
#include "layers/gradient_layer.h"
#include "layers/sdf_layer.h"

#include <SDL2/SDL.h>
#include <stdint.h>

bool is_running = false;

LayerStack stack;
u_int32_t *buffer      = NULL;
u_int32_t *temp_buffer = NULL;

bool setup() {
    setup_display();

    // setup color buffers
    buffer      = malloc(sizeof(uint32_t) * window_width * window_height);
    temp_buffer = malloc(sizeof(uint32_t) * window_width * window_height);
    if (!buffer || !temp_buffer) {
        return false;
    }

    // === LAYER SETUP ===
    layer_stack_init(&stack);

    // TODO: when adding to stack, the stack system creates a base layer with a color buffer
    Layer *gradient = create_gradient_layer(0xFF0000FF, 0xFFFFD700, M_PI / 4.0f);
    layer_stack_push(&stack, gradient);

    Layer *circle = create_sdf_layer(SDF_SHAPE_CIRCLE, 0.4, -1, 0.1, 0.5, 0.5);
    circle->blend = BLEND_ADD;
    layer_stack_push(&stack, circle);

    return true;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)
            is_running = false;
        break;
    }
}

void update() {
    // clear main output buffer
    for (int i = 0; i < window_width * window_height; i++)
        buffer[i] = 0x0;

    for (int i = 0; i < stack.count; i++) {
        Layer *layer = stack.items[i];

        // optional update function call
        // if (layer->update)
        //     layer->update(layer->data, dt);

        // clear temp buffer
        for (int j = 0; j < window_width * window_height; ++j)
            temp_buffer[j] = 0x0;

        // generate layer output into temp
        layer->process(layer->data, temp_buffer, window_width, window_height);

        // blend into main output buffer
        // for (int j = 0; j < window_width * window_height; ++j) {
        //     buffer[j] = blend_colors(buffer[j], temp_buffer[j], layer->blend);
        // }

        // TEMP: TODO: just copy for now
        for (int j = 0; j < window_width * window_height; ++j)
            buffer[j] = temp_buffer[j];
    }
}

void render() {
    render_color_buffer(buffer);
    SDL_RenderPresent(renderer);
}

int main() {
    is_running = init_window() && setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    layer_stack_free(&stack);
    destroy_window();

    return 0;
}
