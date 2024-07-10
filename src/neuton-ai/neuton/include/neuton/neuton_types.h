#ifndef _NEUTON_TYPES_H_
#define _NEUTON_TYPES_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief 8-bit signed integer type definition.
 */
typedef int8_t neuton_i8_t;

/**
 * @brief 8-bit unsigned integer type definition.
 */
typedef uint8_t neuton_u8_t;

/**
 * @brief 16-bit signed integer type definition.
 */
typedef int16_t neuton_i16_t;

/**
 * @brief 16-bit unsigned integer type definition.
 */
typedef uint16_t neuton_u16_t;

/**
  * @brief 32-bit signed integer type definition.
  */
typedef int32_t neuton_i32_t;

/**
 * @brief 32-bit unsigned integer type definition.
 */
typedef uint32_t neuton_u32_t;

/**
 * @brief 64-bit signed integer type definition.
 */
typedef int64_t neuton_i64_t;

/**
 * @brief 64-bit unsigned integer type definition.
 */
typedef uint64_t neuton_u64_t;

/**
 * @brief 32-bit floating-point type definition.
 */
typedef float   neuton_f32_t;

/**
 * @brief 64-bit floating-point type definition.
 */
typedef double  neuton_f64_t;

/**
 * @brief Generic Neuton operation status code
 */
typedef enum neuton_status_e
{
    /** Operation successful */
    NEUTON_STATUS_SUCCESS,

    /** The operation failed with an unspecified error */
    NEUTON_STATUS_UNSPECIFIED_ERROR,

    /** The argument supplied to the operation was invalid */
    NEUTON_STATUS_INVALID_ARGUMENT,

    /** The argument supplied to the operation was NULL */
    NEUTON_STATUS_NULL_ARGUMENT,

    /** The requested operation was not available */
    NEUTON_STATUS_UNAVAILABLE,

    /** The operation or service not supported */
    NEUTON_STATUS_NOT_SUPPORTED
} neuton_status_t;

/**
 * @brief Statistical features mask type for feature extracting API
 * 
 */
typedef union neuton_nn_features_statistical_mask_u
{
    struct
    {
        bool min      : 1; // Minimum
        bool max      : 1; // Maximum
        bool range    : 1; // Range
        bool mean     : 1; // Mean
        bool mad      : 1; // Mean Absolute Deviation
        bool skew     : 1; // Skewness
        bool kur      : 1; // Kurtosis
        bool std      : 1; // Standard Deviation
        bool rms      : 1; // Root Mean Square
        bool mcr      : 1; // Mean-crossing Rate
        bool zcr      : 1; // Zero-crossing Rate
        bool tcr      : 1; // Threshold-crossing Rate
        bool p2p_lf   : 1; // Peak-to-Peak Low Frequency
        bool p2p_hf   : 1; // Peak-to-Peak High Frequency
        bool absmean  : 1; // Absolute mean
        bool amdf     : 1; // Average magnitude difference
        bool p_scr    : 1; // Positive sigma crossing rate
        bool n_scr    : 1; // Negative sigma crossing rate
        bool psoz     : 1; // Percentage of signal over zero
        bool psom     : 1; // Percentage of signal over mean
        bool psos     : 1; // Percentage of signal over sigma
        bool crest    : 1; // Crest factor
        bool rds      : 1; // Root Difference Square
        bool autocorr : 1; // Autocorrelation
        bool hjorth_m : 1; // Hjorth Mobility
        bool hjorth_c : 1; // Hjorth Complexity
    } is;
    neuton_u32_t all;
} neuton_nn_features_stat_mask_t;

/**
 * @brief Spectral features mask type for feature extracting API
 * 
 */
typedef union neuton_nn_features_spectral_mask_u
{   
    struct
    {
        bool spectrum   : 1; // Frequency spectrum @note changing this bit has no effect, enabled by default
        bool peaks_freq : 1; // Peaks frequency indexes in spectrum
        bool peaks_ampl : 1; // Peaks amplitude values in spectrum
        bool ampl_spectrum : 1; // Amplitude spectrum
    } is;
    neuton_u16_t all;
} neuton_nn_features_spectral_mask_t;

/**
 * @brief Mask for all avaliable features for feature extraction
 * 
 */
typedef union neuton_nn_features_mask_u
{
    struct
    {
        /** Spectral features mask */
        neuton_nn_features_spectral_mask_t spectral;

        /** Dummy 2 bytes for proper memory aligment on different architectures, 
         * will be replaced with new features */
        neuton_u16_t dummy;

        /** Statistical features mask */
        neuton_nn_features_stat_mask_t stat;
    } features;
    neuton_u64_t all;
} neuton_nn_features_mask_t;

/**
 * @brief Neuton error codes
 */
typedef enum neuton_nn_err_e
{
    /** Library inferences free limit expired, 
     * please contact support@neuton.ai */
    NEUTON_NN_ERR_FREE_LIMIT_EXPIRED = -128,

    /** Invalid argument error */
    NEUTON_NN_ERR_INVALID_ARGUMENT   = -127,
} neuton_nn_err_t;

/**
 * @brief Neuton model task types
 */
typedef enum neuton_nn_task_e
{
    /** Multiclass classification task */
    NEUTON_NN_TASK_MULT_CLASS   = 0,

    /** Binary classification task*/
    NEUTON_NN_TASK_BIN_CLASS    = 1,

    /** Regression task */
    NEUTON_NN_TASK_REGRESSION   = 2,

    /** Anomaly Detection task */
    NEUTON_NN_TASK_ANOMALY_DETECTION = 3
} neuton_nn_task_t;

/**
 * @brief Neuton input scaling type
 */
typedef enum neuton_nn_input_scaling_e
{
    /** Uses unified(one) scaling factor for all input features */
    NEUTON_NN_INPUT_SCALING_UNIFIED   = 0,

    /** Uses unique scaling factors for each individual input feature */
    NEUTON_NN_INPUT_SCALING_UNIQUE    = 1,

    /** Input features is not used by solution */
    NEUTON_NN_INPUT_SCALING_UNDEFINED  = 2,
} neuton_nn_input_scaling_t;

/**
 * @brief Input features for signal processing & model inference,
 *        can only be obtained using the @ref neuton_nn_feed_inputs() API call.
 */
struct neuton_input_features_s;
typedef struct neuton_input_features_s neuton_input_features_t;

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_TYPES_H_ */