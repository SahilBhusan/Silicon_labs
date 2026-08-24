#include "aws_cloud.h"

static bool s_aws_ready = false;
static uint32_t s_publish_count = 0;

workflow_status_t aws_cloud_init(void)
{
    s_aws_ready = true;
    s_publish_count = 0;
    return WORKFLOW_STATUS_OK;
}

workflow_status_t aws_cloud_publish_report(const secure_packet_t * packet)
{
    if ((packet == NULL) || (packet->length == 0u)) {
        return WORKFLOW_STATUS_ERROR;
    }
    if (!s_aws_ready) {
        return WORKFLOW_STATUS_NOT_READY;
    }

    ++s_publish_count;
    return WORKFLOW_STATUS_OK;
}

uint32_t aws_cloud_get_publish_count(void)
{
    return s_publish_count;
}
