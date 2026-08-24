#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WORKFLOW_AUDIO_SAMPLE_COUNT 160u
#define WORKFLOW_PACKET_BUFFER_SIZE 256u
#define WORKFLOW_SPECIES_NAME_SIZE 32u

typedef enum {
    WORKFLOW_STATUS_OK = 0,
    WORKFLOW_STATUS_ERROR = 1,
    WORKFLOW_STATUS_NOT_READY = 2,
    WORKFLOW_STATUS_BUFFER_TOO_SMALL = 3
} workflow_status_t;

typedef struct {
    uint32_t lux;
    bool valid;
} light_sensor_sample_t;

typedef struct {
    int16_t samples[WORKFLOW_AUDIO_SAMPLE_COUNT];
    size_t sample_count;
    uint32_t sample_rate_hz;
    bool valid;
} mic_audio_frame_t;

typedef struct {
    uint32_t rms_level;
    uint32_t peak_level;
    uint32_t zero_crossings;
    bool bird_activity_detected;
} dsp_features_t;

typedef struct {
    char species[WORKFLOW_SPECIES_NAME_SIZE];
    uint8_t confidence_percent;
    bool behavior_alert;
} ml_classification_t;

typedef struct {
    uint32_t temperature_centi_c;
    uint32_t humidity_centi_percent;
    light_sensor_sample_t light;
    dsp_features_t audio_features;
    ml_classification_t classification;
} workflow_sensor_report_t;

typedef struct {
    char payload[WORKFLOW_PACKET_BUFFER_SIZE];
    size_t length;
    uint32_t integrity_tag;
    bool encrypted;
} secure_packet_t;

#ifdef __cplusplus
}
#endif
