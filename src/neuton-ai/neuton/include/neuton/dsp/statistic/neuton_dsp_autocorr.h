/**
 *
 * @defgroup neuton_dsp_statistic_autocorr Autocorrelation
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_AUTOCORR_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_AUTOCORR_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif


/**
 * @brief Calculate Autocorrelation value in the floating-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[in]       lag       Number of samples use for lag of signal
 * @param[in, out]  p_ctx     Optional pointer to the statistics context, this function will use
 *                            <pre> p_ctx->value.sum and/or p_ctx->value.var </pre> for calculation if it exist,
 *                            the calculated value of variance will be written to context for further use
 *
 * @return  neuton_f32_t  Autocorrelation value in the vector
 */
neuton_f32_t neuton_dsp_autocorr_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                    const neuton_u8_t lag, neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Calculate Autocorrelation value in the INT8 fixed-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[in]       lag       Number of samples use for lag of signal
 * @param[in, out]  p_ctx     Optional pointer to the statistics context, this function will use
 *                            <pre> p_ctx->value.sum and/or p_ctx->value.var </pre> for calculation if it exist,
 *                            the calculated value of variance will be written to context for further use
 *
 * @return  neuton_i16_t  Autocorrelation value in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_autocorr_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                    const neuton_u8_t lag, neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Calculate Autocorrelation value in the INT16 fixed-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[in]       lag       Number of samples use for lag of signal
 * @param[in, out]  p_ctx     Optional pointer to the statistics context, this function will use
 *                            <pre> p_ctx->value.sum and/or p_ctx->value.var </pre> for calculation if it exist,
 *                            the calculated value of variance will be written to context for further use
 *
 * @return  neuton_i16_t  Autocorrelation value in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_autocorr_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                    const neuton_u8_t lag, neuton_dsp_stat_ctx_i16_t* p_ctx);


#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_AUTOCORR_FUNCTIONS_H_ */

/**
 * @}
 */
