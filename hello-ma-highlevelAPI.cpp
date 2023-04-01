#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"
#include <stdio.h>

int main(int argc, char** argv) {
    ma_result result;
    ma_engine engine;

    if (argc < 2) {
        printf("No input file.");
        return EXIT_FAILURE;
    }

    result = ma_engine_init(nullptr, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
        return -1;
    }

    ma_engine_play_sound(&engine, argv[1], nullptr);

    printf("Press Enter to quit...");
    getchar();

    //ma_noise_read_pcm_frames()

    ma_engine_uninit(&engine);

    return EXIT_SUCCESS;
}
