#include "layer.h"
#include "layer_stack.h"
#include "layers/gradient_layer.h"
#include "layers/math_layer.h"
#include "layers/noise_layer.h"

#include <locale.h>
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FRAME_DELAY 0.033f // seconds (~30 FPS)

// const char *palette = " .:-=+*#%@";
// const char *palette = "0123456789";
// const char *palette = "Ñ@#W$9876543210?!abc;:+=-,._ ";
// const char *palette = "█▓▒░ ";
static const char *palette[] = {"█", "▓", "▒", "░", " "};
// chars = "█▓▒░⌂☺☻♠♣♦♥◘○◙♂♀♪♫☼►◄↕‼¶§▬↨↑↓→←∟↔▲▼ "  # Dwarf Fortress-inspired characters

const char *map_value_to_char(float v) {
    if (v < 0.0f)
        v = 0.0f;
    if (v > 1.0f)
        v = 1.0f;

    int palette_len = sizeof(palette) / sizeof(palette[0]);
    int idx         = round(v * (palette_len - 1));
    return palette[idx];
}

float get_elapsed(struct timespec *prev) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    float elapsed = (now.tv_sec - prev->tv_sec) + (now.tv_nsec - prev->tv_nsec) / 1e9f;
    *prev         = now;
    return elapsed;
}

void draw_overlay_ui(int width, int height, LayerStack *stack) {
    int start = height - 4;
    mvprintw(start + 0, 0, "== Overlay UI ==");
    mvprintw(start + 1, 0, "Layers: %d", stack->count);

    for (int i = 0; i < stack->count; i++) {
        Layer *layer          = stack->items[i];
        const char *blend_str = "UNKNOWN";
        switch (layer->blend) {
        case BLEND_REPLACE:
            blend_str = "REPLACE";
            break;
        case BLEND_ADD:
            blend_str = "ADD";
            break;
        case BLEND_MULTIPLY:
            blend_str = "MULTIPLY";
            break;
        case BLEND_MAX:
            blend_str = "MAX";
            break;
        }
        mvprintw(start++, 0, " %d. %s [%s]", i + 1, layer->name, blend_str);
    }

    mvprintw(start++, 0, "Press 'q' to quit, 'u' to toggle UI");

    // mvprintw(start + 2, 0, "Press 'q' to quit, 'u' to toggle UI");
    // mvprintw(start + 3, 0, "Aspect corrected. Math layer active.");
}

int main(void) {
    setlocale(LC_ALL, "");

    // init screen
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE); // don't block on getch()
    keypad(stdscr, TRUE);  // enable arrow keys and such

    // get terminal size
    int width, height;
    getmaxyx(stdscr, height, width);

    // get aspect ratio of screen
    float screen_aspect = (float) width / (float) height;
    float char_aspect   = 0.5f; // most terminals, tune as needed
    float aspect        = screen_aspect * char_aspect;

    // allocate greyscale buffer
    Cell *buffer = malloc(sizeof(Cell) * width * height);
    if (!buffer) {
        endwin();
        fprintf(stderr, "Failed to allocate buffer\n");
        return 1;
    }

    // init layer stack
    LayerStack stack;
    layer_stack_init(&stack);

    // add some layers
    Layer *math = create_math_layer(math_func_sine_rings, 1.0f, 2.0f);
    // Layer *math = create_math_layer(math_func_spiral, 1.0f, 2.0f);
    // math->blend = BLEND_REPLACE;
    layer_stack_push(&stack, math);

    // Layer *gradient = create_gradient_layer();
    // gradient->blend = BLEND_REPLACE; // base image
    // layer_stack_push(&stack, gradient);

    // Layer *noise = create_noise_layer(0.4f);
    // noise->blend = BLEND_ADD; // add sparkles on top
    // layer_stack_push(&stack, noise);

    // timing
    struct timespec last_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);

    int show_ui  = 1;
    int ui_lines = 6 + stack.count;

    int ch;
    while (1) {
        // console input
        ch = getch();
        if (ch == 'q' || ch == 27)
            break;
        if (ch == 'u')
            show_ui = !show_ui;

        float dt = get_elapsed(&last_time);

        // process all layers
        layer_stack_update_and_process(&stack, buffer, width, height, aspect, dt);

        erase();

        // render to terminal
        int draw_height = show_ui ? height - ui_lines : height;
        for (int y = 0; y < draw_height; y++) {
            move(y, 0);
            for (int x = 0; x < width; x++) {
                float v = buffer[y * width + x].value;
                addstr(map_value_to_char(v));
            }
        }

        if (show_ui)
            draw_overlay_ui(width, height, &stack);

        refresh();
        usleep((int) (FRAME_DELAY * 1e6));
    }

    // cleanup
    layer_stack_free(&stack);
    free(buffer);
    endwin();
    return 0;
}
