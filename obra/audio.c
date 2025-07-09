#include "audio.h"

#include "config.h"
#include "engine.h"

// #include <dr_wav.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sample_t samples[MAX_TRACKS] = {0};
PaStream *audio_stream       = NULL;

// Audio buffer for mixing
static float audio_buffer[FRAMES_PER_BUFFER];
static int active_samples[MAX_TRACKS]   = {0};
static int sample_positions[MAX_TRACKS] = {0};

int audio_init(void) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        return -1;
    }

    err = Pa_OpenDefaultStream(&audio_stream,
                               0,                 // input channels
                               1,                 // output channels
                               paFloat32,         // sample format
                               SAMPLE_RATE,       // sample rate
                               FRAMES_PER_BUFFER, // frames per buffer
                               audio_callback,    // callback function
                               NULL);             // user data

    if (err != paNoError) {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        return -1;
    }

    err = Pa_StartStream(audio_stream);
    if (err != paNoError) {
        fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
        return -1;
    }

    return 0;
}

void audio_cleanup(void) {
    if (audio_stream) {
        Pa_StopStream(audio_stream);
        Pa_CloseStream(audio_stream);
    }
    Pa_Terminate();

    // Free sample data
    for (int i = 0; i < MAX_TRACKS; i++) {
        if (samples[i].data) {
            free(samples[i].data);
            samples[i].data = NULL;
        }
    }
}

int audio_play_sample(int track, int step) {
    if (track < 0 || track >= MAX_TRACKS)
        return -1;
    if (!samples[track].data || samples[track].length == 0)
        return -1;

    active_samples[track]   = 1;
    sample_positions[track] = 0;

    return 0;
}

int audio_callback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo,
                   PaStreamCallbackFlags statusFlags, void *userData) {
    (void) input;
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    float *out = (float *) output;

    // Clear buffer
    memset(audio_buffer, 0, frameCount * sizeof(float));

    // Mix active samples
    // for (int track = 0; track < MAX_TRACKS; track++) {
    //     if (active_samples[track] && samples[track].data) {
    //         for (unsigned long i = 0; i < frameCount; i++) {
    //             if (sample_positions[track] < samples[track].length) {
    //                 audio_buffer[i] += samples[track].data[sample_positions[track]] * 0.3f; // Reduce volume
    //                 sample_positions[track]++;
    //             } else {
    //                 active_samples[track] = 0;
    //                 break;
    //             }
    //         }
    //     }
    // }
    //
    // // Copy to output
    // for (unsigned long i = 0; i < frameCount; i++) {
    //     // Clamp to prevent clipping
    //     if (audio_buffer[i] > 1.0f)
    //         audio_buffer[i] = 1.0f;
    //     if (audio_buffer[i] < -1.0f)
    //         audio_buffer[i] = -1.0f;
    //     out[i] = audio_buffer[i];
    // }

    return paContinue;
}
