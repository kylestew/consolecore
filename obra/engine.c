#include "engine.h"

#include "audio.h"
#include "config.h"

#include <dr_wav.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

engine_state_t engine_state = {0};

void engine_init(void) {
    memset(&engine_state, 0, sizeof(engine_state_t));
    engine_state.bpm           = 120;
    engine_state.step_duration = SAMPLE_RATE * 60 / (engine_state.bpm * 4); // 16th notes
    engine_state.current_step  = 0;
    engine_state.step_counter  = 0;
    engine_state.playing       = 0;

    // Initialize all tracks
    for (int i = 0; i < MAX_TRACKS; i++) {
        engine_state.tracks[i].active = 0;
        for (int j = 0; j < PATTERN_LENGTH; j++) {
            engine_state.tracks[i].steps[j] = 0;
        }
    }
}

void engine_cleanup(void) {
    // Nothing to clean up in engine
}

int engine_load_sample(int track, const char *filename) {
    if (track < 0 || track >= MAX_TRACKS)
        return -1;

    // Free existing sample data
    if (samples[track].data) {
        free(samples[track].data);
        samples[track].data = NULL;
    }

    drwav wav;
    if (!drwav_init_file(&wav, filename, NULL)) {
        fprintf(stderr, "Failed to load WAV file: %s\n", filename);
        return -1;
    }

    // Check if mono
    if (wav.channels != 1) {
        fprintf(stderr, "Only mono WAV files are supported: %s\n", filename);
        drwav_uninit(&wav);
        return -1;
    }

    // Allocate buffer
    samples[track].length = wav.totalPCMFrameCount;
    if (samples[track].length > MAX_SAMPLE_LENGTH) {
        samples[track].length = MAX_SAMPLE_LENGTH;
    }

    samples[track].data = malloc(samples[track].length * sizeof(float));
    if (!samples[track].data) {
        drwav_uninit(&wav);
        return -1;
    }

    // Read samples
    drwav_read_pcm_frames_f32(&wav, samples[track].length, samples[track].data);

    // Copy filename
    const char *basename = strrchr(filename, '/');
    if (basename) {
        basename++;
    } else {
        basename = filename;
    }
    strncpy(samples[track].name, basename, MAX_SAMPLE_NAME - 1);
    samples[track].name[MAX_SAMPLE_NAME - 1] = '\0';

    drwav_uninit(&wav);
    return 0;
}

void engine_update(void) {
    if (!engine_state.playing)
        return;

    engine_state.step_counter++;

    if (engine_state.step_counter >= engine_state.step_duration) {
        engine_state.step_counter = 0;

        // Trigger samples for current step
        for (int track = 0; track < MAX_TRACKS; track++) {
            if (engine_state.tracks[track].active && engine_state.tracks[track].steps[engine_state.current_step]) {
                audio_play_sample(track, engine_state.current_step);
            }
        }

        // Advance to next step
        engine_state.current_step++;
        if (engine_state.current_step >= PATTERN_LENGTH) {
            engine_state.current_step = 0;
        }
    }
}

void engine_toggle_step(int track, int step) {
    if (track < 0 || track >= MAX_TRACKS)
        return;
    if (step < 0 || step >= PATTERN_LENGTH)
        return;

    engine_state.tracks[track].steps[step] = !engine_state.tracks[track].steps[step];
    engine_state.tracks[track].active      = 1; // Mark track as active
}

void engine_start_stop(void) {
    engine_state.playing = !engine_state.playing;
    if (!engine_state.playing) {
        engine_state.current_step = 0;
        engine_state.step_counter = 0;
    }
}

void engine_set_bpm(int new_bpm) {
    engine_state.bpm           = new_bpm;
    engine_state.step_duration = SAMPLE_RATE * 60 / (engine_state.bpm * 4);
}

int engine_get_step(int track, int step) {
    if (track < 0 || track >= MAX_TRACKS)
        return 0;
    if (step < 0 || step >= PATTERN_LENGTH)
        return 0;

    return engine_state.tracks[track].steps[step];
}

void engine_set_step(int track, int step, int value) {
    if (track < 0 || track >= MAX_TRACKS)
        return;
    if (step < 0 || step >= PATTERN_LENGTH)
        return;

    engine_state.tracks[track].steps[step] = value;
    if (value) {
        engine_state.tracks[track].active = 1;
    }
}