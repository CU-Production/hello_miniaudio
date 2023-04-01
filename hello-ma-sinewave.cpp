//
// Created by Admin on 2023/4/1.
//

#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

#include <stdio.h>

#define DEVICE_FORMAT       ma_format_f32
#define DEVICE_CHANNELS     2
#define DEVICE_SAMPLE_RATE  48000

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_waveform* pSineWave;
    MA_ASSERT(pDevice->playback.channels == DEVICE_CHANNELS);

    pSineWave = (ma_waveform*)pDevice->pUserData;
    MA_ASSERT(pSineWave != nullptr);

    ma_waveform_read_pcm_frames(pSineWave, pOutput, frameCount, nullptr);

    (void)pInput; // not used
}

int main()
{
    ma_waveform sineWave;
    ma_device_config deviceConfig;
    ma_device device;
    ma_waveform_config sineWaveConfig;

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = DEVICE_FORMAT;
    deviceConfig.playback.channels = DEVICE_CHANNELS;
    deviceConfig.sampleRate = DEVICE_SAMPLE_RATE;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &sineWave;

    if (ma_device_init(nullptr, &deviceConfig, &device) != MA_SUCCESS) {
        printf("Failed to open playback device.\n");
        return -4;
    }

    printf("Device Name: %s\n", device.playback.name);

    sineWaveConfig = ma_waveform_config_init(DEVICE_FORMAT, DEVICE_CHANNELS, DEVICE_SAMPLE_RATE, ma_waveform_type_sine, 0.2, 220);
//    sineWaveConfig = ma_waveform_config_init(DEVICE_FORMAT, DEVICE_CHANNELS, DEVICE_SAMPLE_RATE, ma_waveform_type_square, 0.2, 220);
//    sineWaveConfig = ma_waveform_config_init(DEVICE_FORMAT, DEVICE_CHANNELS, DEVICE_SAMPLE_RATE, ma_waveform_type_triangle, 0.2, 220);
//    sineWaveConfig = ma_waveform_config_init(DEVICE_FORMAT, DEVICE_CHANNELS, DEVICE_SAMPLE_RATE, ma_waveform_type_sawtooth, 0.2, 220);
    if (ma_waveform_init(&sineWaveConfig, &sineWave) != MA_SUCCESS) {
        printf("Failed to init sinewave.\n");
        return -5;
    }

    if (ma_device_start(&device) != MA_SUCCESS) {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&device);
        return -6;
    }

    printf("Press Enter to quit...\n");
    getchar();

    ma_device_uninit(&device);

    return 0;
}
