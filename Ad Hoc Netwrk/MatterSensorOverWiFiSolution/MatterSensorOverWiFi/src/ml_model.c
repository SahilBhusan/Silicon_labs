#include "ml_model.h"

#include <string.h>

static bool s_ml_ready = false;

workflow_status_t ml_model_init(void)
{
    s_ml_ready = true;
    return WORKFLOW_STATUS_OK;
}

workflow_status_t ml_model_classify(const dsp_features_t * features, ml_classification_t * classification)
{
    if ((features == NULL) || (classification == NULL)) {
        return WORKFLOW_STATUS_ERROR;
    }
    if (!s_ml_ready) {
        return WORKFLOW_STATUS_NOT_READY;
    }

    if (features->bird_activity_detected) {
        (void) strncpy(classification->species, "Unknown bird", sizeof(classification->species) - 1u);
        classification->species[sizeof(classification->species) - 1u] = '\0';
        classification->confidence_percent = 72u;
        classification->behavior_alert = features->peak_level > 900u;
    } else {
        (void) strncpy(classification->species, "No bird activity", sizeof(classification->species) - 1u);
        classification->species[sizeof(classification->species) - 1u] = '\0';
        classification->confidence_percent = 95u;
        classification->behavior_alert = false;
    }

    return WORKFLOW_STATUS_OK;
}
