#ifndef UI_H
#define UI_H

#include "config.h"

#include <ncurses.h>

#define MAX_TRACKS 8
#define PATTERN_LENGTH 16
#define MAX_SAMPLE_NAME 32

// UI state
typedef struct {
    int cursor_x;
    int cursor_y;
    int selected_track;
    int selected_step;
    int playing;
    int bpm;
} ui_state_t;

// Function declarations
int ui_init(void);
void ui_cleanup(void);

int ui_get_input(void);
void ui_handle_input(int ch);

void ui_draw(void);
// void ui_draw_pattern(void);
// void ui_draw_info(void);
// void ui_draw_cursor(void);

// External variables
extern ui_state_t ui_state;

#endif // UI_H
