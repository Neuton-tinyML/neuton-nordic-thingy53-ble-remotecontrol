#ifndef _NEUTON_NN_PRIVATE_INTERFACES_PROCESS_FEATURES_H_
#define _NEUTON_NN_PRIVATE_INTERFACES_PROCESS_FEATURES_H_

#include <neuton/nn/neuton_nn_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE
 * @brief Macro to declare feature processing interface functions for various data types and processing modes.
 *
 * All declared functions have the following prototype:
 * @code
 * neuton_status_t neuton_nn_process_features_<mode>_<input_type>_<output_type>(neuton_nn_t* p_nn);
 * @endcode
 * where:
 *   - <mode>        : scale_vector, scale_window, or dsp
 *   - <input_type>  : i8, i16, or f32 (input data type)
 *   - <output_type> : q8, q16, or f32 (output/target data type)
 */
#define NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(interface_name)                               \
    neuton_status_t neuton_nn_process_features_##interface_name(neuton_nn_input_t*        p_input, \
                                                                neuton_nn_dsp_pipeline_t* p_dsp)

/**
 * @brief Scale a vector of input features to the target data type.
 *
 * These functions perform scaling of a single vector of input features from the original data type
 * (int8, int16, or float32) to the target quantized or floating-point type (q8, q16, or f32).
 * Scaling is performed using per-feature min/max values provided in the input context.
 *
 * @param[in, out] p_input        Pointer to the input processing context @ref neuton_nn_input_t
 * @param[in, out] p_dsp          Pointer to the DSP pipeline context @ref neuton_nn_dsp_pipeline_t
 * @return Status code indicating success or error.
 *
 * @note Example functions: neuton_nn_process_features_scale_vector_i8_q8, neuton_nn_process_features_scale_vector_f32_q16, etc.
 */
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_i8_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_i8_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_i8_f32);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_i16_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_i16_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_i16_f32);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_f32_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_f32_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_vector_f32_f32);

/**
 * @brief Scale a window (matrix) of input features to the target data type.
 *
 * These functions perform scaling of a window (matrix) of input features, where each row or column
 * represents a feature over a time window, from the original data type to the target type.
 * Scaling is performed using per-feature min/max values and supports selective scaling based on feature masks.
 *
 * @param[in, out] p_input        Pointer to the input processing context @ref neuton_nn_input_t
 * @param[in, out] p_dsp          Pointer to the DSP pipeline context @ref neuton_nn_dsp_pipeline_t
 * @return Status code indicating success or error.
 *
 * @note Example functions: neuton_nn_process_features_scale_window_i8_q8, neuton_nn_process_features_scale_window_f32_f32, etc.
 */
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_i8_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_i8_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_i8_f32);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_i16_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_i16_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_i16_f32);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_f32_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_f32_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(scale_window_f32_f32);

/**
 * @brief Extract and scale DSP features from input data.
 *
 * These functions perform digital signal processing (DSP) feature extraction (such as statistical or spectral features)
 * from the input data and then scale the extracted features to the target data type.
 * The extraction and scaling are performed according to the configuration in the neural network context.
 *
 * @param[in, out] p_input        Pointer to the input processing context @ref neuton_nn_input_t
 * @param[in, out] p_dsp          Pointer to the DSP pipeline context @ref neuton_nn_dsp_pipeline_t
 * @return Status code indicating success or error.
 *
 * @note Example functions: neuton_nn_process_features_dsp_i8_q8, neuton_nn_process_features_dsp_f32_f32, etc.
 */
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_i8_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_i8_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_i8_f32);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_i16_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_i16_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_i16_f32);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_f32_q8);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_f32_q16);
NEUTON_NN_DECLARE_PROCESS_FEATURES_INTERFACE(dsp_f32_f32);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_PRIVATE_INTERFACES_PROCESS_FEATURES_H_ */