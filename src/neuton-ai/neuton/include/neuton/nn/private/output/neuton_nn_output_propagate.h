#ifndef _NEUTON_NN_PRIVATE_INTERFACES_OUTPUT_PROPAGATE_H_
#define _NEUTON_NN_PRIVATE_INTERFACES_OUTPUT_PROPAGATE_H_

#include <neuton/nn/neuton_nn_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Propagate neural network outputs to the model output structure.
 *
 * These functions transfer the output neuron values from the internal buffer (of the corresponding data type)
 * to the model output structure. They may also apply any required post-processing such as activation or scaling.
 *
 * @param[in, out] p_model    Pointer to model context @ref neuton_nn_model_t
 *
 * @note
 * - Use neuton_nn_output_propagate_q8() for 8-bit quantized models.
 * - Use neuton_nn_output_propagate_q16() for 16-bit quantized models.
 * - Use neuton_nn_output_propagate_f32() for 32-bit floating point models.
 */
void neuton_nn_output_propagate_q8(neuton_nn_model_t* p_model);
void neuton_nn_output_propagate_q16(neuton_nn_model_t* p_model);
void neuton_nn_output_propagate_f32(neuton_nn_model_t* p_model);

/**
 * @brief Dequantize neural network outputs to 32-bit floating point.
 *
 * These functions convert the output values from quantized format (8-bit or 16-bit) to 32-bit floating point format,
 * using the scaling parameters defined in the model context.
 *
 * @param[in, out] p_model    Pointer to model context @ref neuton_nn_model_t
 *
 * @note
 * - Use neuton_nn_output_dequantize_q8_f32() for 8-bit quantized outputs.
 * - Use neuton_nn_output_dequantize_q16_f32() for 16-bit quantized outputs.
 */
void neuton_nn_output_dequantize_q8_f32(neuton_nn_model_t* p_model);
void neuton_nn_output_dequantize_q16_f32(neuton_nn_model_t* p_model);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_PRIVATE_INTERFACES_OUTPUT_PROPAGATE_H_ */