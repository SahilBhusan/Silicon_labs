#include "light_sensor.h"

static bool s_light_sensor_ready = false;
static uint32_t s_light_lux = 325;

workflow_status_t light_sensor_init(void)
{
    s_light_sensor_ready = true;
    return WORKFLOW_STATUS_OK;
}

workflow_status_t light_sensor_read(light_sensor_sample_t * sample)
{
    if (sample == NULL) {
        return WORKFLOW_STATUS_ERROR;
    }
    if (!s_light_sensor_ready) {
        return WORKFLOW_STATUS_NOT_READY;
    }

    s_light_lux = (s_light_lux + 37u) % 1200u;
    sample->lux = s_light_lux;
    sample->valid = true;
    return WORKFLOW_STATUS_OK;
}
