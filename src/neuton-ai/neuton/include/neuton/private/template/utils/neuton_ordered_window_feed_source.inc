#include <neuton/private/neuton_defs.h>

#ifndef FUNC_TEMPLATE_INPUT_TYPE
    #error "FUNC_TEMPLATE_INPUT_TYPE is not defined!"
#endif

#ifndef FUNC_TEMPLATE_OUTPUT_TYPE
    #error "FUNC_TEMPLATE_OUTPUT_TYPE is not defined!"
#endif

#define INPUT_T     CONCAT3(neuton, FUNC_TEMPLATE_INPUT_TYPE, t)
#define OUTPUT_T    CONCAT3(neuton, FUNC_TEMPLATE_OUTPUT_TYPE, t)   

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t FUNCTION_NAME(neuton_ordered_window_feed, FUNC_TEMPLATE_INPUT_TYPE)
                          (neuton_ordered_window_ctx_t* p_ctx, 
                          const INPUT_T* p_input, neuton_u16_t num)
{
    const neuton_u16_t max_samples_num      = p_ctx->max_samples_num;
    const neuton_u16_t uniq_features_num    = p_ctx->uniq_features_num;

    OUTPUT_T* p_window          = p_ctx->p_window.FUNC_TEMPLATE_OUTPUT_TYPE;
    neuton_u16_t current_sample = p_ctx->current_sample;
    neuton_u16_t samples_left   = p_ctx->max_samples_num - p_ctx->current_sample;
    neuton_u16_t loop_cnt       = num > samples_left ? samples_left : num;
    neuton_u16_t stride;

    while (loop_cnt)
    {
        for (size_t i = 0; i < uniq_features_num; i++)
        {
            stride = current_sample + (i * max_samples_num);
            p_window[stride] = *p_input++;
        }
        
        current_sample++;
        loop_cnt--;
    }
    samples_left =  max_samples_num - current_sample;

    if (samples_left == 0)
        p_ctx->current_sample = 0;
    else
        p_ctx->current_sample = current_sample;

    return samples_left;
}

// ///////////////////////////////////////////////////////////////////////////

#define IS_UNIQ_FEATURE_USED(index, mask)     (bool)(mask[index >> 3] & (1U << (index % 8)))

neuton_u16_t FUNCTION_NAME(neuton_ordered_window_feed_bymask, FUNC_TEMPLATE_INPUT_TYPE)
                          (neuton_ordered_window_ctx_t* p_ctx, const INPUT_T* p_input,
                          neuton_u16_t num, const neuton_u8_t* p_usage_mask)
{
    const neuton_u16_t max_samples_num      = p_ctx->max_samples_num;
    const neuton_u16_t uniq_features_num    = p_ctx->uniq_features_num;

    OUTPUT_T* p_window          = p_ctx->p_window.FUNC_TEMPLATE_OUTPUT_TYPE;
    neuton_u16_t current_sample = p_ctx->current_sample;
    neuton_u16_t samples_left   = p_ctx->max_samples_num - p_ctx->current_sample;
    neuton_u16_t loop_cnt       = num > samples_left ? samples_left : num;
    neuton_u16_t collected      = 0;
    neuton_u16_t stride;

    while (loop_cnt)
    {
        collected = 0;
        for (size_t i = 0; i < uniq_features_num; i++)
        {
            if (IS_UNIQ_FEATURE_USED(i, p_usage_mask))
            {
                stride = current_sample + (collected * max_samples_num);
                p_window[stride] = *p_input;
                collected++;
            }
            p_input++;
        }
        
        current_sample++;
        loop_cnt--;
    }

    p_ctx->uniq_features_collected = collected;
    samples_left =  max_samples_num - current_sample;

    if (samples_left == 0)
        p_ctx->current_sample = 0;
    else
        p_ctx->current_sample = current_sample;

    return samples_left;
}