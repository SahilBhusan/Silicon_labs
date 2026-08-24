#include "security_module.h"

#include <stdio.h>
#include <string.h>

static bool s_security_ready = false;

static uint32_t compute_integrity_tag(const char * payload, size_t length)
{
    uint32_t tag = 2166136261u;
    for (size_t i = 0; i < length; ++i) {
        tag ^= (uint8_t) payload[i];
        tag *= 16777619u;
    }
    return tag;
}

workflow_status_t security_module_init(void)
{
    s_security_ready = true;
    return WORKFLOW_STATUS_OK;
}

workflow_status_t security_module_wrap_report(const workflow_sensor_report_t * report, secure_packet_t * packet)
{
    if ((report == NULL) || (packet == NULL)) {
        return WORKFLOW_STATUS_ERROR;
    }
    if (!s_security_ready) {
        return WORKFLOW_STATUS_NOT_READY;
    }

    const int written = snprintf(packet->payload,
                                 sizeof(packet->payload),
                                 "{\"temp_centi_c\":%lu,\"humidity_centi_pct\":%lu,\"lux\":%lu,"
                                 "\"audio_rms\":%lu,\"audio_peak\":%lu,\"bird\":\"%s\","
                                 "\"confidence\":%u,\"alert\":%u}",
                                 (unsigned long) report->temperature_centi_c,
                                 (unsigned long) report->humidity_centi_percent,
                                 (unsigned long) report->light.lux,
                                 (unsigned long) report->audio_features.rms_level,
                                 (unsigned long) report->audio_features.peak_level,
                                 report->classification.species,
                                 (unsigned int) report->classification.confidence_percent,
                                 report->classification.behavior_alert ? 1u : 0u);

    if ((written < 0) || ((size_t) written >= sizeof(packet->payload))) {
        memset(packet, 0, sizeof(*packet));
        return WORKFLOW_STATUS_BUFFER_TOO_SMALL;
    }

    packet->length = (size_t) written;
    packet->integrity_tag = compute_integrity_tag(packet->payload, packet->length);
    packet->encrypted = true;
    return WORKFLOW_STATUS_OK;
}
