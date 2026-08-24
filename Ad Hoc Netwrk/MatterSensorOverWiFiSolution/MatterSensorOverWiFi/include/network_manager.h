#pragma once

#include "workflow_types.h"

#ifdef __cplusplus
extern "C" {
#endif

workflow_status_t network_manager_init(void);
workflow_status_t network_manager_publish_local(const secure_packet_t * packet);
uint32_t network_manager_get_forward_count(void);

#ifdef __cplusplus
}
#endif
