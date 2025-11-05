#ifndef _NEUTON_NN_PRIVATE_INTERFACES_RUN_INFERENCE_H_
#define _NEUTON_NN_PRIVATE_INTERFACES_RUN_INFERENCE_H_

#include <neuton/nn/neuton_nn_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run neural network inference for 8-bit quantized model.
 *
 * This function performs a forward pass (inference) of the neural network using 8-bit quantized weights,
 * activations, and neuron buffers. The function selects the input source (raw input or extracted features)
 * based on the model meta information and computes the output by propagating data through all layers.
 *
 * @param[in,out] p_nn Pointer to the neural network context structure (@ref neuton_nn_t).
 */
void neuton_nn_run_model_inference_q8(neuton_nn_t* p_nn);

/**
 * @brief Run neural network inference for 16-bit quantized model.
 *
 * This function performs a forward pass (inference) of the neural network using 16-bit quantized weights,
 * activations, and neuron buffers. The function selects the input source (raw input or extracted features)
 * based on the model meta information and computes the output by propagating data through all layers.
 *
 * @param[in,out] p_nn Pointer to the neural network context structure (@ref neuton_nn_t).
 */
void neuton_nn_run_model_inference_q16(neuton_nn_t* p_nn);

/**
 * @brief Run neural network inference for 32-bit floating point model.
 *
 * This function performs a forward pass (inference) of the neural network using 32-bit floating point weights,
 * activations, and neuron buffers. The function selects the input source (raw input or extracted features)
 * based on the model meta information and computes the output by propagating data through all layers.
 *
 * @param[in,out] p_nn Pointer to the neural network context structure (@ref neuton_nn_t).
 */
void neuton_nn_run_model_inference_f32(neuton_nn_t* p_nn);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_PRIVATE_INTERFACES_RUN_INFERENCE_H_ */