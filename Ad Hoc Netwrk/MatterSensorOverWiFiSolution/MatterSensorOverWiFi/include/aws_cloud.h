#pragma once

#include "workflow_types.h"

#ifdef __cplusplus
extern "C" {
#endif

workflow_status_t aws_cloud_init(void);
workflow_status_t aws_cloud_publish_report(const secure_packet_t * packet);
uint32_t aws_cloud_get_publish_count(void);

#ifdef __cplusplus
}
#endif
