#include "dsp_module.h"

static bool s_dsp_ready = false;

static uint32_t abs_i16(int16_t value)
{
    return (value < 0) ? (uint32_t) (-value) : (uint32_t) value;
}

workflow_status_t dsp_module_init(void)
{
    s_dsp_ready = true;
    return WORKFLOW_STATUS_OK;
}

workflow_status_t dsp_module_process_audio(const mic_audio_frame_t * frame, dsp_features_t * features)
{
    if ((frame == NULL) || (features == NULL) || (frame->sample_count == 0u)) {
        return WORKFLOW_STATUS_ERROR;
    }
    if (!s_dsp_ready) {
        return WORKFLOW_STATUS_NOT_READY;
    }

    uint32_t sum_abs = 0;
    uint32_t peak = 0;
    uint32_t zero_crossings = 0;
    int16_t previous = frame->samples[0];

    for (size_t i = 0; i < frame->sample_count; ++i) {
        const int16_t sample = frame->samples[i];
        const uint32_t magnitude = abs_i16(sample);
        sum_abs += magnitude;
        if (magnitude > peak) {
            peak = magnitude;
        }
        if (((previous < 0) && (sample >= 0)) || ((previous >= 0) && (sample < 0))) {
            ++zero_crossings;
        }
        previous = sample;
    }

    features->rms_level = sum_abs / (uint32_t) frame->sample_count;
    features->peak_level = peak;
    features->zero_crossings = zero_crossings;
    features->bird_activity_detected = (features->rms_level > 450u) && (features->zero_crossings > 6u);
    return WORKFLOW_STATUS_OK;
}
