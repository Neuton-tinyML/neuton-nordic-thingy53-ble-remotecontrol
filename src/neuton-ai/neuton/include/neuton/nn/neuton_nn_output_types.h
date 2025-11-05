#ifndef _NEUTON_NN_OUTPUT_TYPES_H_
#define _NEUTON_NN_OUTPUT_TYPES_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decoded output structure for classification tasks
 */
typedef struct neuton_nn_decoded_output_classif_s
{
    neuton_u16_t predicted_class; /**< Predicted class index */
    neuton_u16_t num_classes;     /**< Number of classes in the model */

    /**
     * @brief Pointer to probabilities for each class
     */
    union
    {
        const neuton_f32_t* p_f32; /**< Probabilities for f32 models or after dequantization */
        const neuton_u8_t*  p_q8;  /**< Probabilities for q8 models */
        const neuton_u16_t* p_q16; /**< Probabilities for q16 models */
    } probabilities;
} neuton_nn_decoded_output_classif_t;

/**
 * @brief Decoded output structure for regression tasks
 */
typedef struct neuton_nn_decoded_output_regress_s
{
    neuton_u16_t        outputs_num; /**< Number of regression outputs */
    const neuton_f32_t* p_outputs;   /**< Pointer to regression output values */

    /**
     * @brief Meta information for regression output (internal use only)
     */
    struct
    {
        const neuton_f32_t* p_scale_min;         /**< Pointer to minimum scale values */
        const neuton_f32_t* p_scale_max;         /**< Pointer to maximum scale values */
    } meta;
} neuton_nn_decoded_output_regress_t;

/**
 * @brief Decoded output structure for anomaly detection tasks
 */
typedef struct neuton_nn_decoded_output_anomaly_s
{
    neuton_f32_t score; /**< Anomaly score value */

    /**
     * @brief Meta information for regression-anomaly output (internal use only)
     */
    struct
    {
        const neuton_f32_t* p_scale_min;         /**< Pointer to minimum scale values */
        const neuton_f32_t* p_scale_max;         /**< Pointer to maximum scale values */
        const neuton_f32_t* p_average_embedding; /**< Pointer to average embedding values */
    } meta;
} neuton_nn_decoded_output_anomaly_t;

/**
 * @brief Union of decoded output structures for all supported model tasks
 */
typedef union neuton_nn_decoded_output_u
{
    neuton_nn_decoded_output_classif_t classif;    /**< Decoded output for classification */
    neuton_nn_decoded_output_regress_t regression; /**< Decoded output for regression */
    neuton_nn_decoded_output_anomaly_t anomaly;    /**< Decoded output for anomaly detection */
} neuton_nn_decoded_output_t;

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_OUTPUT_TYPES_H_ */