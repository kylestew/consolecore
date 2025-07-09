#include "audio.h"
// #include "engine.h"
#include "ui.h"

#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static volatile int running = 1;

void handle_signal(int sig) {
    (void) sig;
    running = 0;
}

int main(int argc, char *argv[]) {
    // Initialize signal handlers
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Initialize audio system
    if (audio_init() != 0) {
        fprintf(stderr, "Failed to initialize audio\n");
        return 1;
    }

    // // Load samples
    // for (int i = 1; i < argc && i <= MAX_TRACKS; i++) {
    //     if (engine_load_sample(i - 1, argv[i]) != 0) {
    //         fprintf(stderr, "Failed to load sample: %s\n", argv[i]);
    //     }
    // }

    // Initialize UI
    if (ui_init() != 0) {
        fprintf(stderr, "Failed to initialize UI\n");
        audio_cleanup();
        return 1;
    }

    // Initialize engine
    // engine_init();

    // Main loop
    while (running) {
        int ch = ui_get_input();

        if (ch == 'q' || ch == 'Q') {
            break;
        }

        ui_handle_input(ch);
        //     engine_update();
        //     ui_draw();

        usleep(16667); // ~60 FPS
                       //
    }

    // Cleanup
    ui_cleanup();
    // engine_cleanup();
    audio_cleanup();

    return 0;
}
