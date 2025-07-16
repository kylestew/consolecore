#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define FPS 30

extern int window_width;
extern int window_height;

extern SDL_Renderer *renderer;

bool init_window();
void destroy_window();

void setup_display();

// void clear_color_buffer(uint32_t color);
void render_color_buffer(u_int32_t *buffer);

void draw_pixel(int x, int y, uint32_t color);

#endif // DISPLAY_H
