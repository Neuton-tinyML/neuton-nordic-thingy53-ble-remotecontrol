/**
 *
 * @defgroup neuton_utils_sliding_win Sliding window
 * @{
 * @ingroup neuton_utils
 *
 * @brief
 *
 */
#ifndef _NEUTON_UTILS_SLIDING_WINDOW_H_
#define _NEUTON_UTILS_SLIDING_WINDOW_H_

#include <neuton/neuton_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Sliding window callback function. Called when window buffer is ready
 * 
 * @param p_window          Pointer to window buffer
 * @param window_size       Window buffer size in samples
 * @param p_user_ctx        Pointer to user context
 */
typedef void(*neuton_sliding_window_cb_t)(void* p_window, neuton_u16_t window_size,
                                         void* p_user_ctx);

/**
 * @brief Sliding window context block
 */
typedef struct neuton_sliding_window_ctx_s
{
    /** Pointer to window buffer */
    void* p_window;

    /** On window ready user callback */
    neuton_sliding_window_cb_t on_ready_cb;

    /** Current window buffer fill */
    uint32_t current_fill;

    /** Sample size in bytes */
    neuton_u16_t sample_size;

    /** Window buffer size in samples */
    neuton_u16_t window_size;

    /** Window hop in samples. Must be less or equal @window_size*/
    neuton_u16_t window_hop;

    /** Pointer to user context. Can be accessed in callback function */
    void* p_user_ctx;
} neuton_sliding_window_ctx_t;

/**
 * @brief Initialize sliding window context
 * 
 * @param[out]  p_ctx         Context to be initialized 
 * @param[in]   p_window      Pointer to window buffer
 * @param[in]   window_size   Window buffer size in samples
 * @param[in]   sample_size   Sample size in bytes 
 * @param[in]   window_hop    Window hop in samples. Must be less or equal @window_size
 * @param[in]   cb            On window ready user callback
 * @param[in]   p_user_ctx    Pointer to user context
 *  
 * @return @ref neuton_status_t
 */
neuton_status_t neuton_sliding_window_init(neuton_sliding_window_ctx_t* p_ctx, void* p_window,
                                            neuton_u16_t window_size, neuton_u16_t sample_size,
                                            neuton_u16_t window_hop, neuton_sliding_window_cb_t cb,
                                            void* p_user_ctx);

/**
 * @brief Feeds samples to the sliding window
 * 
 * @param[in, out]  p_ctx         Sliding window context, should be initialized first @ref neuton_sliding_window_init
 * @param[in]       p_samples     Input data samples
 * @param[in]       samples_num   Number of data samples
 */
void neuton_sliding_window_feed(neuton_sliding_window_ctx_t* p_ctx, void* p_samples, 
                                neuton_u16_t samples_num);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_UTILS_SLIDING_WINDOW_H_ */

/**
 * @}
 */
