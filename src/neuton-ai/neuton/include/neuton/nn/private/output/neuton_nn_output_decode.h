#ifndef _NEUTON_NN_PRIVATE_INTERFACES_OUTPUT_DECODE_H_
#define _NEUTON_NN_PRIVATE_INTERFACES_OUTPUT_DECODE_H_

#include <neuton/nn/neuton_nn_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decode neural network outputs for classification tasks.
 *
 * These functions process the raw model outputs for classification tasks, converting them into
 * predicted class indices and class probabilities. The decoding is performed according to the
 * output data type (f32, q8, or q16).
 *
 * @param[in] p_model_output      Pointer to model output structure @ref neuton_nn_model_t
 * @param[out] p_decoded_output   Pointer to decoded output structure @ref neuton_nn_decoded_output_t
 *
 * @note
 * - Use neuton_nn_output_decode_classification_f32() for 32-bit floating point outputs.
 * - Use neuton_nn_output_decode_classification_q8() for 8-bit quantized outputs.
 * - Use neuton_nn_output_decode_classification_q16() for 16-bit quantized outputs.
 */
void neuton_nn_output_decode_classification_f32(neuton_nn_model_output_t*   p_model_output,
                                                neuton_nn_decoded_output_t* p_decoded_output);
void neuton_nn_output_decode_classification_q8(neuton_nn_model_output_t*   p_model_output,
                                               neuton_nn_decoded_output_t* p_decoded_output);
void neuton_nn_output_decode_classification_q16(neuton_nn_model_output_t*   p_model_output,
                                                neuton_nn_decoded_output_t* p_decoded_output);

/**
 * @brief Decode neural network outputs for regression tasks.
 *
 * This function processes the raw model outputs for regression tasks, converting them into
 * final regression values.
 *
 * @param[in] p_model_output      Pointer to model output structure @ref neuton_nn_model_t
 * @param[out] p_decoded_output   Pointer to decoded output structure @ref neuton_nn_decoded_output_t
 *
 * @note
 * - Use neuton_nn_output_decode_regression_f32() for 32-bit floating point outputs.
 */
void neuton_nn_output_decode_regression_f32(neuton_nn_model_output_t*   p_model_output,
                                            neuton_nn_decoded_output_t* p_decoded_output);

/**
 * @brief Decode neural network outputs for anomaly detection tasks.
 *
 * This function processes the raw model outputs for anomaly detection tasks, converting them into
 * final anomaly score value.
 *
 * @param[in] p_model_output      Pointer to model output structure @ref neuton_nn_model_t
 * @param[out] p_decoded_output   Pointer to decoded output structure @ref neuton_nn_decoded_output_t
 *
 * @note
 * - Use neuton_nn_output_decode_anomaly_f32() for 32-bit floating point outputs.
 */
void neuton_nn_output_decode_anomaly_f32(neuton_nn_model_output_t*   p_model_output,
                                         neuton_nn_decoded_output_t* p_decoded_output);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_PRIVATE_INTERFACES_OUTPUT_DECODE_H_ */