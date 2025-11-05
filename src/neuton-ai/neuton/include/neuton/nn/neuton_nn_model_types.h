#ifndef _NEUTON_NN_MODEL_TYPES_H_
#define _NEUTON_NN_MODEL_TYPES_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Neuton model task types
 */

/** For preprocessor */
#define __NEUTON_NN_TASK_MULT_CLASS        0
#define __NEUTON_NN_TASK_BIN_CLASS         1
#define __NEUTON_NN_TASK_REGRESSION        2
#define __NEUTON_NN_TASK_ANOMALY_DETECTION 3

typedef enum neuton_nn_model_task_e
{
    NEUTON_NN_TASK_MULT_CLASS        = __NEUTON_NN_TASK_MULT_CLASS, /**< Multiclass classification task */
    NEUTON_NN_TASK_BIN_CLASS         = __NEUTON_NN_TASK_BIN_CLASS, /**< Binary classification task */
    NEUTON_NN_TASK_REGRESSION        = __NEUTON_NN_TASK_REGRESSION, /**< Regression task */
    NEUTON_NN_TASK_ANOMALY_DETECTION = __NEUTON_NN_TASK_ANOMALY_DETECTION  /**< Anomaly Detection task */
} neuton_nn_model_task_t;

/**
 * @brief Model input usage type
 */
typedef union neuton_nn_model_uses_as_input_u
{
    struct
    {
        bool input     : 1; /**< Use raw input features */
        bool extracted : 1; /**< Use extracted features */
    } features;
    neuton_u8_t all; /**< All usage flags as bitmask */
} neuton_nn_model_uses_as_input_t;

/**
 * @brief Model parameters for 32-bit floating point precision
 */
typedef struct neuton_nn_model_params_f32_s
{
    const neuton_f32_t* p_weights;     /**< Pointer to weights array */
    const neuton_f32_t* p_act_weights; /**< Pointer to activation function weights */
    neuton_f32_t*       p_neurons;     /**< Pointer to neurons buffer */
} neuton_nn_model_params_f32_t;

/**
 * @brief Model parameters for 16-bit quantized precision
 */
typedef struct neuton_nn_model_params_q16_s
{
    const neuton_i16_t* p_weights;     /**< Pointer to weights array */
    const neuton_u16_t* p_act_weights; /**< Pointer to activation function weights */
    neuton_u16_t*       p_neurons;     /**< Pointer to neurons buffer */
} neuton_nn_model_params_q16_t;

/**
 * @brief Model parameters for 8-bit quantized precision
 */
typedef struct neuton_nn_model_params_q8_s
{
    const neuton_i8_t* p_weights;     /**< Pointer to weights array */
    const neuton_u8_t* p_act_weights; /**< Pointer to activation function weights */
    neuton_u8_t*       p_neurons;     /**< Pointer to neurons buffer */
} neuton_nn_model_params_q8_t;

/**
 * @brief Union of model parameters for all supported types
 */
typedef union neuton_nn_model_params_u
{
    neuton_nn_model_params_q8_t  q8;  /**< 8-bit quantized parameters */
    neuton_nn_model_params_q16_t q16; /**< 16-bit quantized parameters */
    neuton_nn_model_params_f32_t f32; /**< 32-bit floating point parameters */
} neuton_nn_model_params_t;

/**
 * @brief Model meta information structure
 */
typedef struct neuton_nn_model_meta_s
{
    const char* p_solution_id_str; /**< Solution ID string */

    /**< Number of internal links for each neuron */
    const neuton_u16_t* p_neuron_internal_links_num;
    /**< Number of external links for each neuron */
    const neuton_u16_t* p_neuron_external_links_num;

    const neuton_u16_t* p_output_neurons_indices; /**< Indices of output neurons */
    const neuton_u16_t* p_neuron_links;           /**< Neuron links array */
    const neuton_u8_t*  p_neuron_act_type_mask;   /**< Activation function type mask for neurons */
    const neuton_u16_t  outputs_num;              /**< Number of model outputs */
    const neuton_u16_t  neurons_num;              /**< Number of neurons in the model */
    const neuton_u32_t  weights_num;              /**< Number of weights in the model */
    const neuton_nn_model_task_t task;            /**< Model task type */

    const neuton_nn_model_uses_as_input_t uses_as_input; /**< Model input usage type */
} neuton_nn_model_meta_t;

/**
 * @brief Model output structure
 */
typedef struct neuton_nn_model_output_s
{
    union
    {
        neuton_f32_t* p_f32;  /**< Pointer to 32-bit float output buffer */
        neuton_u8_t*  p_q8;   /**< Pointer to 8-bit quantized output buffer */
        neuton_u16_t* p_q16;  /**< Pointer to 16-bit quantized output buffer */
        void*         p_void; /**< Generic pointer to output buffer */
    } memory;                 /**< Union of output buffer pointers */
    neuton_u16_t num;         /**< Number of output values */
} neuton_nn_model_output_t;

/**
 * @brief Model context structure
 */
typedef struct neuton_nn_model_s
{
    neuton_nn_model_meta_t   meta;   /**< Model meta information */
    neuton_nn_model_params_t params; /**< Model parameters */
    neuton_nn_model_output_t output; /**< Model output */
} neuton_nn_model_t;

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_MODEL_TYPES_H_ */