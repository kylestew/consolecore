#ifndef ENGINE_H
#define ENGINE_H

#include "config.h"

#include <stdint.h>

// Pattern structure
typedef struct {
    int steps[PATTERN_LENGTH];
    int active;
} track_pattern_t;

// Engine state
typedef struct {
    track_pattern_t tracks[MAX_TRACKS];
    int current_step;
    int step_counter;
    int step_duration;
    int bpm;
    int playing;
} engine_state_t;

// Function declarations
void engine_init(void);
void engine_cleanup(void);
int engine_load_sample(int track, const char *filename);
void engine_update(void);
void engine_toggle_step(int track, int step);
void engine_start_stop(void);
void engine_set_bpm(int new_bpm);
int engine_get_step(int track, int step);
void engine_set_step(int track, int step, int value);

// External variables
extern engine_state_t engine_state;

#endif // ENGINE_H