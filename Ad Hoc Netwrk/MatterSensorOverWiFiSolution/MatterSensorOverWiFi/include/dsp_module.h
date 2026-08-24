#pragma once

#include "workflow_types.h"

#ifdef __cplusplus
extern "C" {
#endif

workflow_status_t dsp_module_init(void);
workflow_status_t dsp_module_process_audio(const mic_audio_frame_t * frame, dsp_features_t * features);

#ifdef __cplusplus
}
#endif
