/**
 *
 * @defgroup neuton Neuton.AI C-library
 * @{
 *
 * @details The Neuton library is static C library, written in accordance with the C99 standard and 
 *          has no dependencies other than the standard C language library (libc).
 *          The library does not use any hardware-specific instructions, dynamic memory allocation, 
 *          stack usage is kept to a minimum.
 *
 */

#ifndef _NEUTON_H_
#define _NEUTON_H_

#include <neuton/nn/neuton_nn_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set up the internal components of the Neuton neural network, 
 *        should be called first and once
 * 
 * @param[in, out] p_nn     Pointer to neural network context @ref neuton_nn_t
 *  
 * @return Neuton operation status code @ref neuton_status_t 
 */
neuton_status_t neuton_nn_setup(neuton_nn_t* p_nn);

/**
 * @brief  Feed raw input data to prepare it for signal processing & model inference
 * 
 * @param[in, out] p_nn         Pointer to neural network context @ref neuton_nn_t
 * @param[in] p_input_values    Array of the input data samples, 
 *                              the type of input data is dependent of neural network context neuton_nn_t, use @ref neuton_nn_input_type()
 * @param[in] num_values        Number of the input samples in array, should be a multiple of @ref neuton_nn_uniq_inputs_num()
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
neuton_status_t neuton_nn_feed_inputs(neuton_nn_t* p_nn,
                                      void*        p_input_values,
                                      neuton_u16_t num_values);

/**
 * @brief Running live input features into a Neuton machine learning algorithm (or “ML model”) to inference an output
 * 
 * @details If the operation is succeeded (NEUTON_STATUS_SUCCESS), 
 *          the inference result you can get from p_nn->decoded_output.regression or p_nn->decoded_output.classif depending on your model task
 * 
 * @param[in, out] p_nn     Pointer to neural network context @ref neuton_nn_t
 * 
 * @return Neuton operation status code @ref neuton_status_t 
 */
neuton_status_t neuton_nn_run_inference(neuton_nn_t* p_nn);

/***********************************************************************************************************************
Utility variables and functions
***********************************************************************************************************************/

/**
 * @brief Get neural network input data type @ref neuton_nn_input_type_t 
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 * 
 */
neuton_nn_input_type_t neuton_nn_input_type(const neuton_nn_t* p_nn);

/**
 * @brief Get number of unique input features on which the model was trained,
 *         e.g for features {x, y, z} -> number of unique input features = 3
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 *  
 */
neuton_u16_t neuton_nn_uniq_inputs_num(const neuton_nn_t* p_nn);

/**
 * @brief Get input features window size in feature samples(vectors),
 *         e.g for input window {x0, y0, z0, ..., xn, yn, zn} -> window size = n
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 * 
 */
neuton_u16_t neuton_nn_input_window_size(const neuton_nn_t* p_nn);

/**
 * @brief Get number of subwindows in the input window
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 * 
 */
neuton_u8_t neuton_nn_input_subwindows_num(const neuton_nn_t* p_nn);

/**
 * @brief Get number of model neurons
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 */
neuton_u16_t neuton_nn_model_neurons_num(const neuton_nn_t* p_nn);

/**
 * @brief Get number of model weights
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 */
neuton_u16_t neuton_nn_model_weights_num(const neuton_nn_t* p_nn);

/**
 * @brief Get number of model outputs (predicted targets)
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 */
neuton_u16_t neuton_nn_model_outputs_num(const neuton_nn_t* p_nn);

/**
 * @brief Get model task @ref neuton_nn_model_task_t
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 */
neuton_nn_model_task_t neuton_nn_model_task(const neuton_nn_t* p_nn);

/**
 * @brief Get solution ID in string format
 * 
 * @param[in] p_nn  Pointer to neural network context @ref neuton_nn_t
 */
const char* neuton_nn_solution_id_str(const neuton_nn_t* p_nn);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_H_ */

/**
 * @}
 */
