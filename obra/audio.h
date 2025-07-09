#ifndef AUDIO_H
#define AUDIO_H

#include "config.h"

#include <portaudio.h>
#include <stdint.h>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256
#define MAX_SAMPLE_LENGTH 44100 * 10 // 10 seconds max

// Audio sample structure
typedef struct {
    float *data;
    int length;
    char name[MAX_SAMPLE_NAME];
} sample_t;

// Function declarations
int audio_init(void);
void audio_cleanup(void);
int audio_play_sample(int track, int step);
int audio_callback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData);

// External variables
extern sample_t samples[MAX_TRACKS];
extern PaStream *audio_stream;

#endif // AUDIO_H