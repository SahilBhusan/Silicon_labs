#pragma once

#include "workflow_types.h"

#ifdef __cplusplus
extern "C" {
#endif

workflow_status_t light_sensor_init(void);
workflow_status_t light_sensor_read(light_sensor_sample_t * sample);

#ifdef __cplusplus
}
#endif
