#ifndef _NEUTON_NN_INPUT_TYPES_H_
#define _NEUTON_NN_INPUT_TYPES_H_

#include <neuton/neuton_types.h>
#include <neuton/utils/neuton_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Supported input data types for neural network
 */
typedef enum neuton_nn_input_type_e
{
    NEUTON_NN_INPUT_I8  = 1, /**< 8-bit signed integer input */
    NEUTON_NN_INPUT_I16 = 2, /**< 16-bit signed integer input */
    NEUTON_NN_INPUT_F32 = 4, /**< 32-bit floating point input */
} neuton_nn_input_type_t;

/**
 * @brief Scaling parameters for 8-bit integer input
 */
typedef struct neuton_nn_input_scale_i8_s
{
    const neuton_i8_t* p_min; /**< Pointer to minimum value for scaling */
    const neuton_i8_t* p_max; /**< Pointer to maximum value for scaling */
} neuton_nn_input_scale_i8_t;

/**
 * @brief Scaling parameters for 16-bit integer input
 */
typedef struct neuton_nn_input_scale_i16_s
{
    const neuton_i16_t* p_min; /**< Pointer to minimum value for scaling */
    const neuton_i16_t* p_max; /**< Pointer to maximum value for scaling */
} neuton_nn_input_scale_i16_t;

/**
 * @brief Scaling parameters for 32-bit floating point input
 */
typedef struct neuton_nn_input_scale_f32_s
{
    const neuton_f32_t* p_min; /**< Pointer to minimum value for scaling */
    const neuton_f32_t* p_max; /**< Pointer to maximum value for scaling */
} neuton_nn_input_scale_f32_t;

/**
 * @brief Union of input scaling parameters for all supported types
 */
typedef union neuton_nn_input_scale_u
{
    neuton_nn_input_scale_i8_t  i8;  /**< Scaling for 8-bit integer input */
    neuton_nn_input_scale_i16_t i16; /**< Scaling for 16-bit integer input */
    neuton_nn_input_scale_f32_t f32; /**< Scaling for 32-bit float input */
} neuton_nn_input_scale_t;

/**
 * @brief Union of window context types for input data
 */
typedef union neuton_nn_window_ctx_u
{
    neuton_osl_window_ctx_t     sliding;  /**< Sliding window context */
    neuton_ordered_window_ctx_t discrete; /**< Discrete window context */
} neuton_nn_window_ctx_t;

/**
 * @brief Input features processing context for neural network
 */
typedef struct neuton_nn_input_s
{
    neuton_nn_input_scale_t scale;                /**< Input scaling parameters */
    const neuton_u8_t*      p_used_for_lags_mask; /**< Mask for features used for lags */
    const neuton_u8_t*      p_usage_mask;         /**< Mask for features usage */

    const neuton_nn_input_type_t type; /**< Input data type */
    /**
     * @brief Number of unique input features (axes) in input window,
     *        e.g. for Accel_X, Accel_Y, Accel_Z the num = 3
     */
    const neuton_u16_t unique_num;
    const neuton_u16_t unique_num_used;   /**< Number of unique features used */
    const neuton_u16_t unique_scales_num; /**< Number of unique scales */
    const neuton_u16_t window_size;       /**< Size of input window in samples */
    const neuton_u16_t window_shift;      /**< Shift of input window, while sliding */
    const neuton_u8_t  subwindow_num;     /**< Number of subwindows */
    /**
     * @brief Pointer to the input data buffer
     */
    union
    {
        void*         p_void; /**< Generic pointer to window memory */
        neuton_i8_t*  p_i8;   /**< Pointer to 8-bit integer window memory */
        neuton_i16_t* p_i16;  /**< Pointer to 16-bit integer window memory */
        neuton_f32_t* p_f32;  /**< Pointer to 32-bit float window memory */
    } window_memory;

    neuton_nn_window_ctx_t* p_window_ctx; /**< Pointer to window context */
} neuton_nn_input_t;

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_INPUT_TYPES_H_ */