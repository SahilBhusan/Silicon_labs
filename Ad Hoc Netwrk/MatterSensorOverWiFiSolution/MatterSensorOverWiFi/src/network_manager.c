#include "network_manager.h"

static bool s_network_ready = false;
static uint32_t s_forward_count = 0;

workflow_status_t network_manager_init(void)
{
    s_network_ready = true;
    s_forward_count = 0;
    return WORKFLOW_STATUS_OK;
}

workflow_status_t network_manager_publish_local(const secure_packet_t * packet)
{
    if ((packet == NULL) || (packet->length == 0u)) {
        return WORKFLOW_STATUS_ERROR;
    }
    if (!s_network_ready) {
        return WORKFLOW_STATUS_NOT_READY;
    }

    ++s_forward_count;
    return WORKFLOW_STATUS_OK;
}

uint32_t network_manager_get_forward_count(void)
{
    return s_forward_count;
}
