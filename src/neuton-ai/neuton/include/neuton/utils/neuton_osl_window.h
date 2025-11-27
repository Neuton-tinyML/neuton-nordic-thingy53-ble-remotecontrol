/**
 *
 * @defgroup neuton_osl_window Ordered and sliding by columns window 
 * @{
 * @ingroup neuton_utils
 *
 * @brief
 *
 */
#ifndef _NEUTON_UTILS_ORDERED_SLIDING_WINDOW_H_
#define _NEUTON_UTILS_ORDERED_SLIDING_WINDOW_H_

#include "neuton_ordered_window.h"
#include <neuton/neuton_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

typedef struct neuton_osl_window_ctx_s
{
    /** Ordered window context */
    neuton_ordered_window_ctx_t ord_win;

    /** Window shift in samples, by which the window will be shifted when it is filled. 
     * Must be less or equal @ord_win.max_samples_num
     */
    neuton_u16_t window_shift;

    /** Flag if window should be shifted by window_shift on the next window feed */
    bool is_shift_pending;
} neuton_osl_window_ctx_t;

/**
 * @brief Initialize ordered by colums sliding window context type 
 * 
 * @param[out]   p_ctx               Pointer to the window context which will be initialized
 * @param[in]    p_window            Pointer to window buffer
 * @param[in]    max_samples_num     Maximum number of feature samples in window buffer, feature sample = 1 * uniq_features_num
 * @param[in]    uniq_features_num   Number of unique features in feature sample, e.g feature sample = {x, y, z}, then uniq_features_num = 3
 * @param[in]    window_shift        Window shift in samples by which the window will be shifted when it is filled. Must be less or equal @max_samples_num
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
neuton_status_t neuton_osl_window_init(neuton_osl_window_ctx_t* p_ctx, 
                                    void* p_window, const neuton_u16_t max_samples_num, 
                                    const size_t uniq_features_num,
                                    const neuton_u16_t window_shift);

/**
 * @brief Feeds f32 samples to the floating-point ordered by colums window,
 *        with ordering by feature columns, e.g p_input = [x,y,z,x1,y1,z1] -> p_window = [x,x1,.., y,y1,.., z,z1,..]
 * 
 * @note If window was filled, next call will shift window to the right for each unique feature in window by p_ctx->window_shift
 * 
 * @param[in, out]  p_ctx       Pointer to the window context, should be initialized first @ref neuton_osl_window_init
 * @param[in]       p_input     Pointer to the feature sample buffer
 * @param[in]       num         Number of samples in the input buffer, num = buffer_size / p_ctx->uniq_features_num
 *  
 * @return neuton_u16_t Number of remaining samples to collect window
 */
neuton_u16_t neuton_osl_window_feed_f32(neuton_osl_window_ctx_t* p_ctx,
                                        const neuton_f32_t* p_input, neuton_u16_t num);

/**
 * @brief Feeds INT8 samples to the INT8 ordered by colums window,
 *        with ordering by feature columns, e.g p_input = [x,y,z,x1,y1,z1] -> p_window = [x,x1,.., y,y1,.., z,z1,..]
 * 
 * @param[in, out]  p_ctx       Pointer to the window context, should be initialized first @ref neuton_osl_window_init
 * @param[in]       p_input     Pointer to the feature sample buffer
 * @param[in]       num         Number of samples in the input buffer, num = buffer_size / p_ctx->uniq_features_num
 *  
 * @return neuton_u16_t Number of remaining samples to collect window
 */
neuton_u16_t neuton_osl_window_feed_i8(neuton_osl_window_ctx_t* p_ctx,
                                        const neuton_i8_t* p_input, neuton_u16_t num);

/**
 * @brief Feeds INT16 samples to the INT16 ordered by colums window,
 *        with ordering by feature columns, e.g p_input = [x,y,z,x1,y1,z1] -> p_window = [x,x1,.., y,y1,.., z,z1,..]
 * 
 * @param[in, out]  p_ctx       Pointer to the window context, should be initialized first @ref neuton_osl_window_init
 * @param[in]       p_input     Pointer to the feature sample buffer
 * @param[in]       num         Number of samples in the input buffer, num = buffer_size / p_ctx->uniq_features_num
 *  
 * @return neuton_u16_t Number of remaining samples to collect window
 */
neuton_u16_t neuton_osl_window_feed_i16(neuton_osl_window_ctx_t* p_ctx,
                                        const neuton_i16_t* p_input, neuton_u16_t num);

/**
 * @brief Feeds f32 samples to the floating-point ordered by colums window,
 *        with ordering by feature columns, e.g p_input = [x,y,z,x1,y1,z1] -> p_window = [x,x1,.., y,y1,.., z,z1,..],
 *        usage of inputs column is determined by p_input_usage_mask where each bit represents each unique feature
 * 
 * @param[in, out]  p_ctx           Pointer to the window context, should be initialized first @ref neuton_osl_window_init
 * @param[in]       p_input         Pointer to the feature sample buffer
 * @param[in]       num             Number of samples in the input buffer, num = buffer_size / p_ctx->uniq_features_num
 * @param[in]       p_usage_mask    Input features usage mask
 *  
 * @return neuton_u16_t Number of remaining samples to collect window
 */
neuton_u16_t neuton_osl_window_feed_bymask_f32(neuton_osl_window_ctx_t* p_ctx,
                                                const neuton_f32_t* p_input, neuton_u16_t num,
                                                const neuton_u8_t* p_usage_mask);

/**
 * @brief Feeds INT8 samples to the floating-point ordered by colums window,
 *        with ordering by feature columns, e.g p_input = [x,y,z,x1,y1,z1] -> p_window = [x,x1,.., y,y1,.., z,z1,..],
 *        usage of inputs column is determined by p_input_usage_mask where each bit represents each unique feature
 * 
 * @param[in, out]  p_ctx           Pointer to the window context, should be initialized first @ref neuton_osl_window_init
 * @param[in]       p_input         Pointer to the feature sample buffer
 * @param[in]       num             Number of samples in the input buffer, num = buffer_size / p_ctx->uniq_features_num
 * @param[in]       p_usage_mask    Input features usage mask
 *  
 * @return neuton_u16_t Number of remaining samples to collect window
 */
neuton_u16_t neuton_osl_window_feed_bymask_i8(neuton_osl_window_ctx_t* p_ctx,
                                            const neuton_i8_t* p_input, neuton_u16_t num,
                                            const neuton_u8_t* p_usage_mask);

/**
 * @brief Feeds INT16 samples to the floating-point ordered by colums window,
 *        with ordering by feature columns, e.g p_input = [x,y,z,x1,y1,z1] -> p_window = [x,x1,.., y,y1,.., z,z1,..],
 *        usage of inputs column is determined by p_input_usage_mask where each bit represents each unique feature
 * 
 * @param[in, out]  p_ctx           Pointer to the window context, should be initialized first @ref neuton_osl_window_init
 * @param[in]       p_input         Pointer to the feature sample buffer
 * @param[in]       num             Number of samples in the input buffer, num = buffer_size / p_ctx->uniq_features_num
 * @param[in]       p_usage_mask    Input features usage mask
 *  
 * @return neuton_u16_t Number of remaining samples to collect window
 */
neuton_u16_t neuton_osl_window_feed_bymask_i16(neuton_osl_window_ctx_t* p_ctx,
                                                const neuton_i16_t* p_input, neuton_u16_t num,
                                                const neuton_u8_t* p_usage_mask);
#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_UTILS_ORDERED_SLIDING_WINDOW_H_ */

/**
 * @}
 */
