#include "display.h"

SDL_Window *window     = NULL;
SDL_Renderer *renderer = NULL;

SDL_Texture *texture = NULL;

int window_width;
int window_height;

bool init_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initing SDL\n");
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    // larger pixels please - but keep aspect ratio
    window_width  = display_mode.w / 2;
    window_height = display_mode.h / 2;

    // create SDL window
    window = SDL_CreateWindow(NULL,                   //
                              SDL_WINDOWPOS_CENTERED, //
                              SDL_WINDOWPOS_CENTERED, //
                              window_width,           //
                              window_height,          //
                              SDL_WINDOW_BORDERLESS);
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void setup_display() {
    texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
}

void render_color_buffer(u_int32_t *buffer) {
    SDL_UpdateTexture(texture, NULL, buffer, (int) (window_width * sizeof(uint32_t)));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}
