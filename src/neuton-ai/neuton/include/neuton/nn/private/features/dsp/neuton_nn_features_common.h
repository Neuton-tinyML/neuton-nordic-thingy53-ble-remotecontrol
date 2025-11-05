#ifndef _NEUTON_NN_PRIVATE_INTERFACES_FEATURES_COMMON_H_
#define _NEUTON_NN_PRIVATE_INTERFACES_FEATURES_COMMON_H_

#include <neuton/nn/neuton_nn_dsp_pipeline_types.h>

/**
 * @def NEUTON_NN_DECLARE_FEATURE_FUNCTION
 * @brief Macro to declare time-domain DSP feature extraction functions for various data types.
 *
 * All declared functions have the following prototype:
 * @code
 * neuton_sz_t neuton_nn_feature_<feature_name>(
 *     <input_type>*                    p_input,
 *     neuton_sz_t                      num,
 *     <feature_type>*                  p_features,
 *     neuton_nn_features_mask_t        feature_mask,
 *     void*                            p_pipeline_ctx,
 *     neuton_nn_feature_get_arg_cb_t   get_argument,
 *     void*                            p_argument_ctx
 * );
 * @endcode
 * where:
 *   - <feature_name>  : Name of the feature (e.g., mean_i8, std_f32, etc.)
 *   - <input_type>    : Input data type (neuton_i8_t, neuton_i16_t, neuton_f32_t)
 *   - <feature_type>  : Output feature data type (neuton_i16_t, neuton_i32_t, neuton_f32_t)
 *
 * These functions extract one or more time-domain features from the input signal buffer,
 * storing the results in the output feature buffer. The feature_mask parameter allows
 * selective extraction of features. The pipeline context and argument callback provide
 * additional configuration or arguments for feature extraction.
 *
 * @param[in]  p_input         Pointer to the input signal buffer.
 * @param[in]  num             Number of input samples.
 * @param[out] p_features      Pointer to the output feature buffer.
 * @param[in]  feature_mask    Mask specifying which features to extract.
 * @param[in]  p_pipeline_ctx  Pointer to the pipeline context (may be NULL).
 * @param[in]  get_argument    Callback to get feature-specific arguments (may be NULL).
 * @param[in]  p_argument_ctx  Pointer to argument context for the callback (may be NULL).
 * @return     Number of features extracted and written to p_features.
 *
 * @note
 * - Use NEUTON_NN_DECLARE_FEATURE_FUNCTION_I8, NEUTON_NN_DECLARE_FEATURE_FUNCTION_I16, or NEUTON_NN_DECLARE_FEATURE_FUNCTION_F32
 *   to declare feature functions for int8, int16, or float32 input types, respectively.
 *
 * @example
 * // Declaration for mean feature extraction on int8 input:
 * NEUTON_NN_DECLARE_FEATURE_FUNCTION_I8(mean_i8);
 *
 * // Expands to:
 * neuton_sz_t neuton_nn_feature_mean_i8(
 *     neuton_i8_t*                    p_input,
 *     neuton_sz_t                     num,
 *     neuton_i16_t*                   p_features,
 *     neuton_nn_features_mask_t       feature_mask,
 *     void*                           p_pipeline_ctx,
 *     neuton_nn_feature_get_arg_cb_t  get_argument,
 *     void*                           p_argument_ctx
 * );
 */

#define NEUTON_NN_DECLARE_FEATURE_FUNCTION(feature_name, input_type, feature_type)              \
    neuton_sz_t neuton_nn_feature_##feature_name(input_type*                    p_input,        \
                                                 neuton_sz_t                    num,            \
                                                 feature_type*                  p_features,     \
                                                 neuton_nn_features_mask_t      feature_mask,   \
                                                 void*                          p_pipeline_ctx, \
                                                 neuton_nn_feature_get_arg_cb_t get_argument,   \
                                                 void*                          p_argument_ctx)

#define NEUTON_NN_DECLARE_FEATURE_FUNCTION_I8(feature_name) \
    NEUTON_NN_DECLARE_FEATURE_FUNCTION(feature_name, neuton_i8_t, neuton_i16_t)

#define NEUTON_NN_DECLARE_FEATURE_FUNCTION_I16(feature_name) \
    NEUTON_NN_DECLARE_FEATURE_FUNCTION(feature_name, neuton_i16_t, neuton_i32_t)

#define NEUTON_NN_DECLARE_FEATURE_FUNCTION_F32(feature_name) \
    NEUTON_NN_DECLARE_FEATURE_FUNCTION(feature_name, neuton_f32_t, neuton_f32_t)

#endif /* _NEUTON_NN_PRIVATE_INTERFACES_FEATURES_COMMON_H_ */