#include "mic_audio.h"

static bool s_mic_ready = false;
static uint16_t s_frame_seed = 0;

workflow_status_t mic_audio_init(void)
{
    s_mic_ready = true;
    return WORKFLOW_STATUS_OK;
}

workflow_status_t mic_audio_capture_frame(mic_audio_frame_t * frame)
{
    if (frame == NULL) {
        return WORKFLOW_STATUS_ERROR;
    }
    if (!s_mic_ready) {
        return WORKFLOW_STATUS_NOT_READY;
    }

    frame->sample_count = WORKFLOW_AUDIO_SAMPLE_COUNT;
    frame->sample_rate_hz = 16000u;
    frame->valid = true;

    for (size_t i = 0; i < WORKFLOW_AUDIO_SAMPLE_COUNT; ++i) {
        const int16_t base = (int16_t) (((i + s_frame_seed) % 32u) * 64u);
        const int16_t centered = (int16_t) (base - 1024);
        frame->samples[i] = centered;
    }

    s_frame_seed = (uint16_t) (s_frame_seed + 3u);
    return WORKFLOW_STATUS_OK;
}
