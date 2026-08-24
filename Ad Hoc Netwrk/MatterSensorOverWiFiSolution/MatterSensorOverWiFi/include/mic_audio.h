#pragma once

#include "workflow_types.h"

#ifdef __cplusplus
extern "C" {
#endif

workflow_status_t mic_audio_init(void);
workflow_status_t mic_audio_capture_frame(mic_audio_frame_t * frame);

#ifdef __cplusplus
}
#endif
