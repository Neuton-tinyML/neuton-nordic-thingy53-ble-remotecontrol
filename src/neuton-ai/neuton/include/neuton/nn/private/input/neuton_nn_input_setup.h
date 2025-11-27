#ifndef _NEUTON_NN_PRIVATE_INTERFACES_INPUT_SETUP_H_
#define _NEUTON_NN_PRIVATE_INTERFACES_INPUT_SETUP_H_

#include <neuton/nn/neuton_nn_input_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Setup input context for models without windowing.
 *
 * Initializes the input context for models that do not use any windowing strategy.
 * This setup is suitable for models that process single input vectors without temporal context.
 *
 * @param[in,out] p_input_ctx Pointer to the input context structure (@ref neuton_nn_input_t).
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
neuton_status_t neuton_nn_input_setup_no_window(neuton_nn_input_t* p_input_ctx);

/**
 * @brief Setup input context for discrete windowing.
 *
 * Initializes the input context for models that use discrete windowing, where each window is processed independently.
 *
 * @param[in,out] p_input_ctx Pointer to the input context structure (@ref neuton_nn_input_t).
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
neuton_status_t neuton_nn_input_setup_discrete_window(neuton_nn_input_t* p_input_ctx);

/**
 * @brief Setup input context for sliding windowing.
 *
 * Initializes the input context for models that use a sliding window strategy, maintaining a moving window of recent input values.
 *
 * @param[in,out] p_input_ctx Pointer to the input context structure (@ref neuton_nn_input_t).
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
neuton_status_t neuton_nn_input_setup_sliding_window(neuton_nn_input_t* p_input_ctx);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_PRIVATE_INTERFACES_INPUT_SETUP_H_ */