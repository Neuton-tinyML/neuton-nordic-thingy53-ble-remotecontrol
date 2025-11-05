#ifndef _NEUTON_NN_PRIVATE_INTERFACES_INPUT_FEED_H_
#define _NEUTON_NN_PRIVATE_INTERFACES_INPUT_FEED_H_

#include <neuton/nn/neuton_nn_input_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE
 * @brief Macro to declare input feeding interface functions for various windowing and data types.
 *
 * All declared functions have the following prototype:
 * @code
 * neuton_status_t neuton_nn_input_feed_<mode>(neuton_nn_input_t* p_input_ctx,
 *                                             void*              p_input_values,
 *                                             neuton_u16_t       num_values);
 * @endcode
 * where <mode> specifies the windowing/data type strategy.
 */
#define NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(interface_name)                               \
    neuton_status_t neuton_nn_input_feed_##interface_name(neuton_nn_input_t* p_input_ctx,    \
                                                          void*              p_input_values, \
                                                          neuton_u16_t       num_values)

/**
 * @brief Feed input data without windowing.
 *
 * These functions feed input data directly into the input context without applying any windowing.
 * They are suitable for models that process single vectors or do not require temporal context.
 *
 * @param[in,out] p_input_ctx   Pointer to the input context structure (@ref neuton_nn_input_t).
 * @param[in]     p_input_values Pointer to the input values buffer.
 * @param[in]     num_values     Number of input values to feed.
 *
 * @note
 * - Use neuton_nn_input_feed_no_window() for basic input feeding with no internal memory buffer.
 * - Use neuton_nn_input_feed_no_window_extra() if internal extra memory buffer is required.
 */
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(no_window);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(no_window_extra);

/**
 * @brief Feed input data using discrete windowing.
 *
 * These functions feed input data into the input context using a discrete windowing strategy,
 * where each window is processed independently. Masked variants allow selective feature feeding.
 *
 * @param[in,out] p_input_ctx   Pointer to the input context structure (@ref neuton_nn_input_t).
 * @param[in]     p_input_values Pointer to the input values buffer.
 * @param[in]     num_values     Number of input values to feed.
 *
 * @note
 * - Use neuton_nn_input_feed_discrete_window_i8(), neuton_nn_input_feed_discrete_window_i16(), or
 *   neuton_nn_input_feed_discrete_window_f32() for different data types.
 * - Use masked variants for selective feature feeding.
 */
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(discrete_window_i8);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(discrete_window_masked_i8);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(discrete_window_i16);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(discrete_window_masked_i16);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(discrete_window_f32);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(discrete_window_masked_f32);

/**
 * @brief Feed input data using sliding windowing.
 *
 * These functions feed input data into the input context using a sliding window strategy,
 * maintaining a moving window of recent input values. Masked variants allow selective feature feeding.
 *
 * @param[in,out] p_input_ctx   Pointer to the input context structure (@ref neuton_nn_input_t).
 * @param[in]     p_input_values Pointer to the input values buffer.
 * @param[in]     num_values     Number of input values to feed.
 *
 * @note
 * - Use neuton_nn_input_feed_sliding_window_i8(), neuton_nn_input_feed_sliding_window_i16(), or
 *   neuton_nn_input_feed_sliding_window_f32() for different data types.
 * - Use masked variants for selective feature feeding.
 */
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(sliding_window_i8);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(sliding_window_masked_i8);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(sliding_window_i16);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(sliding_window_masked_i16);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(sliding_window_f32);
NEUTON_NN_DECLARE_INPUT_FEED_INTERFACE(sliding_window_masked_f32);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_PRIVATE_INTERFACES_INPUT_FEED_H_ */