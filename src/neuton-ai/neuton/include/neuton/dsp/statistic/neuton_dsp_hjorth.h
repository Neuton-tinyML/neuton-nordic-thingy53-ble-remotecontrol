/**
 *
 * @defgroup neuton_dsp_statistic_hjorth Hjorth Parameters
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_HJORTH_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_HJORTH_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Hjorth Parameters values for F32 signal format
 * 
 */
typedef struct neuton_dsp_hjorth_params_f32_s
{
    /** Hjorth Activity (signal Variance) */
    neuton_f32_t activity;

    /** Hjorth Mobility parameter represents the mean frequency or the proportion of standard deviation 
     * of the power spectrum. This is defined as the square root of variance of the first derivative of the signal y(t)
     * divided by variance of the signal y(t). */
    neuton_f32_t mobility;

    /** Hjorth Complexity parameter represents the change in frequency. 
     * The parameter compares the signal's similarity to a pure sine wave, 
     * where the value converges to 1 if the signal is more similar.
     */
    neuton_f32_t complexity;    
} neuton_dsp_hjorth_params_f32_t;

/**
 * @brief Hjorth Parameters values for INT8 signal format
 * 
 */
typedef struct neuton_dsp_hjorth_params_i8_s
{
    /** Hjort Activity (signal Variance) */
    neuton_i16_t activity;

    /** Hjort Mobility, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR */
    neuton_i16_t mobility;

    /** Hjort Complexity, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR */
    neuton_i16_t complexity;    
} neuton_dsp_hjorth_params_i8_t;

/**
 * @brief Hjorth Parameters values for INT16 signal format
 * 
 */
typedef struct neuton_dsp_hjorth_params_i16_s
{
    /** Hjort Activity (signal Variance) */
    neuton_i32_t activity;

    /** Hjort Mobility, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR */
    neuton_i32_t mobility;

    /** Hjort Complexity, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR */
    neuton_i32_t complexity;    
} neuton_dsp_hjorth_params_i16_t;

/**
 * @brief Calculates Hjorth Parameters in a floating-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[out]      p_params  Calculated Hjorth Parameters @ref neuton_dsp_hjorth_params_f32_t
 * @param[in, out]  p_ctx     Optional pointer to the statistics context,
 *                            this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 */
void neuton_dsp_hjorth_f32(const neuton_f32_t* p_input, neuton_u16_t num, 
                            neuton_dsp_hjorth_params_f32_t* p_params,
                            neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Calculates Hjorth Parameters in a INT8 fixed-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[out]      p_params  Calculated Hjorth Parameters @ref neuton_dsp_hjorth_params_i8_t
 * @param[in, out]  p_ctx     Optional pointer to the statistics context,
 *                            this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 */
void neuton_dsp_hjorth_i8(const neuton_i8_t* p_input, neuton_u16_t num, 
                            neuton_dsp_hjorth_params_i8_t* p_params,
                            neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Calculates Hjorth Parameters in a INT16 fixed-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[out]      p_params  Calculated Hjorth Parameters @ref neuton_dsp_hjorth_params_i16_t
 * @param[in, out]  p_ctx     Optional pointer to the statistics context,
 *                            this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 */
void neuton_dsp_hjorth_i16(const neuton_i16_t* p_input, neuton_u16_t num, 
                            neuton_dsp_hjorth_params_i16_t* p_params,
                            neuton_dsp_stat_ctx_i16_t* p_ctx);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_HJORTH_FUNCTIONS_H_ */

/**
 * @}
 */
