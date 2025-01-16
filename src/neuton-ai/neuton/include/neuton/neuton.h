/**
 *
 * @defgroup neuton Neuton TinyML library
 * @{
 *
 * @details The Neuton library is static C library, written in accordance with the C99 standard and 
 *          has no dependencies other than the standard C language library (libc).
 *          Our library does not use any hardware-specific instructions, dynamic memory allocation, 
 *          stack usage is kept to a minimum.
 *
 */

#ifndef _NEUTON_H_
#define _NEUTON_H_

#include <neuton_generated/neuton_user_types.h>
#include <neuton/neuton_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Set up the internal components of the Neuton, 
 *        should be called first and once
 */
void neuton_nn_setup(void);

/**
 * @brief Feed raw input data to prepare it for signal processing & model inference
 * @warning @ref neuton_nn_setup() should be called once prior to use
 * 
 * @param[in] p_input   Array of the raw input data samples
 * @param[in] num       Number of the input samples in array, should be a multiple of @ref neuton_nn_uniq_inputs_num()
 *  
 * @return Input features ready for signal processing and inference, or Null if it is not ready
 */
neuton_input_features_t* neuton_nn_feed_inputs(const neuton_input_t* p_input, neuton_u16_t num);
 
/**
 * @brief Running live input features into a Neuton machine learning algorithm (or “ML model”) to inference an output
 * 
 * @param[in]  p_input_features     Input features for model inference, obtained from @ref neuton_nn_feed_inputs() API call
 * 
 * @param[out] p_index              For Classification: Index of predicted target(class) with highest probability. 
 *                                  For Regression and Anomaly detection: p_index is not used and always 0
 * 
 * @param[out] pp_outputs           Pointer to the internal buffer with all model outputs.
 *                                  For Classification: contains probabilities of each class (binary/multi classification)
 *                                  For Regression: contains predicted target values
 *                                  For Anomaly detection: contains anomaly score
 * 
 * @return neuton_i16_t       Number of the predicted outputs(classes/values/anomaly score) or the following errors:
 *                                  NEUTON_NN_ERR_INVALID_ARGUMENT      if p_input_features is invalid,
 *                                  NEUTON_NN_ERR_FREE_LIMIT_EXPIRED    if you are using the free version and the number of available inferences has expired,
 *                                                                      for more information please contact us! 
 */
neuton_i16_t neuton_nn_run_inference(neuton_input_features_t* p_input_features, 
                                    neuton_u16_t* p_index, 
                                    const neuton_output_t** pp_outputs);

/**
 * @brief Get number of unique input features on which the model was trained,
 *         e.g for features {x, y, z} -> number of unique input features = 3
 */
neuton_u16_t neuton_nn_uniq_inputs_num(void);

/**
 * @brief Get input features window size in feature samples(vectors),
 *         e.g for input window {x, y, z, ..., xn, yn, zn} -> window size = n
 */
neuton_u16_t neuton_nn_input_window_size(void);

/**
 * @brief Get number of model neurons
 */
neuton_u16_t neuton_nn_model_neurons_num(void);

/**
 * @brief Get number of model weights
 */
neuton_u16_t neuton_nn_model_weights_num(void);

/**
 * @brief Get number of model outputs (predicted targets)
 */
neuton_u16_t neuton_nn_model_outputs_num(void);

/**
 * @brief Get model task @ref neuton_nn_task_t
 */
neuton_nn_task_t neuton_nn_model_task(void);

/**
 * @brief Get model size in bytes (flash usage)
 */
neuton_u32_t neuton_nn_model_size(void);

/**
 * @brief Get model quantization-aware bit size of weights & coefficients (8/16/32 bit)
 */
neuton_u8_t neuton_nn_model_quantization(void);

/**
 * @brief Return true if model uses quantized activation functions, otherwise false
 */
bool neuton_nn_model_activations_quantized(void);

/**
 * @brief Return true if model uses quantized outputs, otherwise false
 */
bool neuton_nn_model_output_quantized(void);

/**
 * @brief Get solution ID in string format
 */
const char* neuton_nn_solution_id_str(void);

/**
 * @brief Get solution input scaling type @ref neuton_nn_input_scaling_t
 */
neuton_nn_input_scaling_t neuton_nn_input_scaling(void);

/**
 * @brief Get a pointer to an array of extracted features masks, the mask describes which features model uses for inference.
 * 
 * @param[in, out] pp_masks_arr     Pointer to extracted features mask array, can be null if extracted features is not used by model
 *
 * @return Number of extracted features masks in array, e.g array length:
 *            0 - if it is not exist, extracted features are not used.
 *            1 - if extracted features are the same for all unique inputs @ref neuton_nn_uniq_inputs_num()
 *            N - if extracted features are different for atleast one unique input feature
 */
neuton_u16_t neuton_nn_extracted_features_used(const neuton_nn_features_mask_t** pp_masks_arr);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_H_ */

/**
 * @}
 */
