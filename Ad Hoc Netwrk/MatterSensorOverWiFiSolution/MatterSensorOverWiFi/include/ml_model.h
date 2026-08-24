#pragma once

#include "workflow_types.h"

#ifdef __cplusplus
extern "C" {
#endif

workflow_status_t ml_model_init(void);
workflow_status_t ml_model_classify(const dsp_features_t * features, ml_classification_t * classification);

#ifdef __cplusplus
}
#endif
