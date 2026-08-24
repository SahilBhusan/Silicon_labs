#pragma once

#include "workflow_types.h"

#ifdef __cplusplus
extern "C" {
#endif

workflow_status_t security_module_init(void);
workflow_status_t security_module_wrap_report(const workflow_sensor_report_t * report, secure_packet_t * packet);

#ifdef __cplusplus
}
#endif
