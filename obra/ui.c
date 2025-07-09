#include "ui.h"

#include "config.h"
// #include "engine.h"

#include <stdio.h>
#include <string.h>

ui_state_t ui_state = {0};

int ui_init(void) {
    // (n)curses init
    initscr();            // "curses mode"
    cbreak();             // input is immediate - no enter needed
    noecho();             // don't echo input to screen
    keypad(stdscr, TRUE); // easier key handling in code
    curs_set(0);          // hide cursor

    // does the current terminal support color?
    if (has_colors()) {
        start_color();                           // enable color
                                                 // setup color pairs
        init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Active step
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Current step
        init_pair(3, COLOR_WHITE, COLOR_BLACK);  // Normal
    }

    ui_state.cursor_x       = 0;
    ui_state.cursor_y       = 0;
    ui_state.selected_track = 0;
    ui_state.selected_step  = 0;
    ui_state.playing        = 0;
    ui_state.bpm            = 120;

    return 0;
}

void ui_cleanup(void) { endwin(); }

int ui_get_input(void) {
    int ch = getch();
    if (ch == ERR) {
        return 0;
    }
    return ch;
}

void ui_handle_input(int ch) {
    switch (ch) {
        // case KEY_LEFT:
        // case 'h':
        //     if (ui_state.selected_step > 0) {
        //         ui_state.selected_step--;
        //     }
        //     break;
        //
        // case KEY_RIGHT:
        // case 'l':
        //     if (ui_state.selected_step < PATTERN_LENGTH - 1) {
        //         ui_state.selected_step++;
        //     }
        //     break;
        //
        // case KEY_UP:
        // case 'k':
        //     if (ui_state.selected_track > 0) {
        //         ui_state.selected_track--;
        //     }
        //     break;
        //
        // case KEY_DOWN:
        // case 'j':
        //     if (ui_state.selected_track < MAX_TRACKS - 1) {
        //         ui_state.selected_track++;
        //     }
        //     break;
        //
        // case '\n':
        // case ' ':
        //     if (ch == '\n') {
        //         engine_toggle_step(ui_state.selected_track, ui_state.selected_step);
        //     } else {
        //         engine_start_stop();
        //         ui_state.playing = engine_state.playing;
        //     }
        //     break;
        //
        // case '+':
        // case '=':
        //     ui_state.bpm += 5;
        //     if (ui_state.bpm > 200)
        //         ui_state.bpm = 200;
        //     engine_set_bpm(ui_state.bpm);
        //     break;
        //
        // case '-':
        //     ui_state.bpm -= 5;
        //     if (ui_state.bpm < 60)
        //         ui_state.bpm = 60;
        //     engine_set_bpm(ui_state.bpm);
        //     break;
    }
}

void ui_draw(void) {
    clear();
    //     ui_draw_pattern();
    //     ui_draw_info();
    //     ui_draw_cursor();
    //     refresh();
}

// void ui_draw_pattern(void) {
//     mvprintw(0, 0, "OBRA - Music Tracker");
//     mvprintw(1, 0, "Track |");
//
//     // Draw step numbers
//     for (int i = 0; i < PATTERN_LENGTH; i++) {
//         mvprintw(1, 8 + i * 3, "%2d", i);
//     }
//     mvprintw(1, 8 + PATTERN_LENGTH * 3, "|");
//
//     // Draw tracks
//     for (int track = 0; track < MAX_TRACKS; track++) {
//         mvprintw(2 + track, 0, "  %d   |", track);
//
//         for (int step = 0; step < PATTERN_LENGTH; step++) {
//             int x = 8 + step * 3;
//             int y = 2 + track;
//
//             if (engine_get_step(track, step)) {
//                 if (step == engine_state.current_step && engine_state.playing) {
//                     attron(COLOR_PAIR(2));
//                     mvprintw(y, x, " X");
//                     attroff(COLOR_PAIR(2));
//                 } else {
//                     attron(COLOR_PAIR(1));
//                     mvprintw(y, x, " X");
//                     attroff(COLOR_PAIR(1));
//                 }
//             } else {
//                 if (step == engine_state.current_step && engine_state.playing) {
//                     attron(COLOR_PAIR(2));
//                     mvprintw(y, x, " -");
//                     attroff(COLOR_PAIR(2));
//                 } else {
//                     mvprintw(y, x, " -");
//                 }
//             }
//         }
//         mvprintw(2 + track, 8 + PATTERN_LENGTH * 3, "|");
//     }
// }
//
// void ui_draw_info(void) {
//     int y = MAX_TRACKS + 3;
//     mvprintw(y, 0, "Controls:");
//     mvprintw(y + 1, 0, "  hjkl/arrows - Navigate");
//     mvprintw(y + 2, 0, "  Enter      - Toggle step");
//     mvprintw(y + 3, 0, "  Space      - Start/Stop");
//     mvprintw(y + 4, 0, "  +/-        - Change BPM");
//     mvprintw(y + 5, 0, "  q          - Quit");
//
//     mvprintw(y, 30, "Status:");
//     mvprintw(y + 1, 30, "  Playing: %s", ui_state.playing ? "Yes" : "No");
//     mvprintw(y + 2, 30, "  BPM: %d", ui_state.bpm);
//     mvprintw(y + 3, 30, "  Step: %d", engine_state.current_step);
//     mvprintw(y + 4, 30, "  Track: %d", ui_state.selected_track);
// }
//
// void ui_draw_cursor(void) {
//     int x = 8 + ui_state.selected_step * 3;
//     int y = 2 + ui_state.selected_track;
//
//     attron(A_REVERSE);
//     mvprintw(y, x, "  ");
//     attroff(A_REVERSE);
// }
