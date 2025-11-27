#ifndef _NEUTON_NN_TYPES_H_
#define _NEUTON_NN_TYPES_H_

#include <neuton/nn/neuton_nn_dsp_pipeline_types.h>
#include <neuton/nn/neuton_nn_input_types.h>
#include <neuton/nn/neuton_nn_model_types.h>
#include <neuton/nn/neuton_nn_output_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Forward declaration of neural network context
 */
struct neuton_nn_s;
typedef struct neuton_nn_s neuton_nn_t;

/***********************************************************************************************************************
Neuton processing interfaces types
***********************************************************************************************************************/

/**
 * @brief Setup internal data structures for processing input features(data), 
 *          collecting data windows, etc
 *
 * @param[in, out] p_input_ctx     Pointer to the input processing context @ref neuton_nn_input_t 
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
typedef neuton_status_t (*neuton_nn_iface_input_setup_t)(neuton_nn_input_t* p_input_ctx);

/**
 * @brief Feed and collect input features to internal data structures for further processing
 * 
 * @param[in, out] p_input_ctx     Pointer to the input processing context @ref neuton_nn_input_t
 * @param[in] p_input_values       Input features data array
 * @param[in] num_values           Number of input features in the array
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
typedef neuton_status_t (*neuton_nn_iface_feed_inputs_t)(neuton_nn_input_t* p_input_ctx,
                                                         void*              p_input_values,
                                                         neuton_u16_t       num_values);
/**
 * @brief Run model inference
 * 
 * @param[in, out] p_nn     Pointer to neural network context @ref neuton_nn_t
 * 
 */
typedef void (*neuton_nn_iface_run_inference_t)(neuton_nn_t* p_nn);

/**
 * @brief Propagate raw model output neurons to the output values structure
 * 
 * @param[in, out] p_model    Pointer to model context @ref neuton_nn_model_t
 * 
 */
typedef void (*neuton_nn_iface_propagate_outputs_t)(neuton_nn_model_t* p_model);

/**
 * @brief Decode raw model outputs to human-readable format depending on the model task
 * 
 * @param[in] p_model_output      Pointer to model output structure @ref neuton_nn_model_t
 * @param[out] p_decoded_output   Pointer to decoded output structure @ref neuton_nn_decoded_output_t
 * 
 */
typedef void (*neuton_nn_iface_decode_outputs_t)(neuton_nn_model_output_t*   p_model_output,
                                                 neuton_nn_decoded_output_t* p_decoded_output);

/**
 * @brief Process input features for model inference, e.g. scaling, filtering, DSP, etc
 * 
 * @param[in, out] p_input        Pointer to the input processing context @ref neuton_nn_input_t
 * @param[in, out] p_dsp          Pointer to the DSP pipeline context @ref neuton_nn_dsp_pipeline_t
 * 
 * @return Neuton operation status code @ref neuton_status_t
 */
typedef neuton_status_t (*neuton_nn_iface_process_features_t)(neuton_nn_input_t*        p_input,
                                                              neuton_nn_dsp_pipeline_t* p_dsp);

/***********************************************************************************************************************
Neuton neural network interfaces structure definition
***********************************************************************************************************************/

typedef struct neuton_nn_interfaces_s
{
    neuton_nn_iface_input_setup_t       input_setup;
    neuton_nn_iface_feed_inputs_t       feed_inputs;
    neuton_nn_iface_process_features_t  process_features;
    neuton_nn_iface_run_inference_t     run_inference;
    neuton_nn_iface_propagate_outputs_t propagate_outputs;
    neuton_nn_iface_decode_outputs_t    decode_outputs;
} neuton_nn_interfaces_t;

/***********************************************************************************************************************
Neuton neural network context definition
***********************************************************************************************************************/
struct neuton_nn_s
{
    /** Input features processing context */
    neuton_nn_input_t input;
    /** DSP pipeline context */
    neuton_nn_dsp_pipeline_t* p_dsp;
    /** Model context */
    neuton_nn_model_t model;
    /** Decoded output results */
    neuton_nn_decoded_output_t decoded_output;
    /** Processing interfaces */
    neuton_nn_interfaces_t interfaces;
};

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_TYPES_H_ */