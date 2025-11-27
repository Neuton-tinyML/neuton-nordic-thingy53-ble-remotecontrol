#include <neuton/private/neuton_defs.h>
#include <string.h>

#ifndef FUNC_TEMPLATE_INPUT_TYPE
    #error "FUNC_TEMPLATE_INPUT_TYPE is not defined!"
#endif

#define INPUT_T                                 CONCAT3(neuton, FUNC_TEMPLATE_INPUT_TYPE, t)
#define neuton_ordered_window_feed              CONCAT2(neuton_ordered_window_feed, FUNC_TEMPLATE_INPUT_TYPE)
#define neuton_ordered_window_feed_bymask       CONCAT2(neuton_ordered_window_feed_bymask, FUNC_TEMPLATE_INPUT_TYPE)

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t FUNCTION_NAME(neuton_osl_window_feed, FUNC_TEMPLATE_INPUT_TYPE)
                          (neuton_osl_window_ctx_t* p_ctx, 
                          const INPUT_T* p_input, neuton_u16_t num)
{
    if (p_ctx->is_shift_pending)
    {
        p_ctx->is_shift_pending = false;

        const neuton_u8_t sample_size = sizeof(INPUT_T);
        const neuton_u16_t feature_window_size_bytes = p_ctx->ord_win.max_samples_num * sample_size;
        const neuton_u32_t tail_size = p_ctx->ord_win.max_samples_num - p_ctx->window_shift;

        for (size_t i = 0; i < p_ctx->ord_win.uniq_features_num; i++)
        {
            INPUT_T* p_feature_window = (INPUT_T*)(p_ctx->ord_win.p_window.i8 + (i * feature_window_size_bytes));

            memmove(p_feature_window, &p_feature_window[p_ctx->window_shift], tail_size * sample_size);
        }

        p_ctx->ord_win.current_sample = tail_size;
    }

    neuton_u16_t samples_left = neuton_ordered_window_feed(&p_ctx->ord_win, p_input, num);

    if (samples_left == 0)
        p_ctx->is_shift_pending = true;

    return samples_left;
}

// ///////////////////////////////////////////////////////////////////////////

neuton_u16_t FUNCTION_NAME(neuton_osl_window_feed_bymask, FUNC_TEMPLATE_INPUT_TYPE)
                          (neuton_osl_window_ctx_t* p_ctx, const INPUT_T* p_input,
                          neuton_u16_t num, const neuton_u8_t* p_usage_mask)
{
    if (p_ctx->is_shift_pending)
    {
        p_ctx->is_shift_pending = false;

        const neuton_u8_t sample_size = sizeof(INPUT_T);
        const neuton_u16_t feature_window_size_bytes = p_ctx->ord_win.max_samples_num * sample_size;
        const neuton_u32_t tail_size = p_ctx->ord_win.max_samples_num - p_ctx->window_shift;

        for (size_t i = 0; i < p_ctx->ord_win.uniq_features_collected; i++)
        {
            INPUT_T* p_feature_window = (INPUT_T*)(p_ctx->ord_win.p_window.i8 + (i * feature_window_size_bytes));

            memmove(p_feature_window, &p_feature_window[p_ctx->window_shift], tail_size * sample_size);
        }

        p_ctx->ord_win.current_sample = tail_size;
    }

    neuton_u16_t samples_left = neuton_ordered_window_feed_bymask(&p_ctx->ord_win, p_input, num, p_usage_mask);

    if (samples_left == 0)
        p_ctx->is_shift_pending = true;

    return samples_left;
}