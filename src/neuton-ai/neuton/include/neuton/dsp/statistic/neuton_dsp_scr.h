/**
 *
 * @defgroup neuton_dsp_statistic_scr Sigma-crossing Rate
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_SCR_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_SCR_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Counts Sigma-crossing rate with respect to Mean, of a floating-point vector.
 *
 * @param[in]       p_input         Pointer to the input vector
 * @param[in]       num             Number of samples in input vector
 * @param[in]       sigma_factor    Sigma multiplier for which the crossing rate will be counted
 * @param[in, out]  p_ctx           Optional pointer to the statistics context,
 *                                  this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 *
 * @return  neuton_f32_t  Sigma-crossing rate in the vector
 */
neuton_f32_t neuton_dsp_scr_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                neuton_dsp_sigma_factor_t sigma_factor, 
                                neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Counts Sigma-crossing rate with respect to Mean, of a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]       p_input         Pointer to the input vector
 * @param[in]       num             Number of samples with 'stride' in input vector
 * @param[in]       sigma_factor    Sigma multiplier for which the crossing rate will be counted
 * @param[in]       stride          Vector element offset stride
 * @param[in, out]  p_ctx           Optional pointer to the statistics context,
 *                                  this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 *
 * @return  neuton_f32_t  Sigma-crossing rate in the vector within a stride
 */
neuton_f32_t neuton_dsp_scr_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                neuton_dsp_sigma_factor_t sigma_factor, size_t stride,
                                neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Counts Sigma-crossing rate with respect to Mean, of a INT8 fixed-point vector.
 *
 * @param[in]       p_input         Pointer to the input vector
 * @param[in]       num             Number of samples in input vector
 * @param[in]       sigma_factor    Sigma multiplier for which the crossing rate will be counted
 * @param[in, out]  p_ctx           Optional pointer to the statistics context,
 *                                  this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 *
 * @return  neuton_i16_t  Sigma-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_scr_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                neuton_dsp_sigma_factor_t sigma_factor, 
                                neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Counts Sigma-crossing rate with respect to Mean, of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]       p_input         Pointer to the input vector
 * @param[in]       num             Number of samples with 'stride' in input vector
 * @param[in]       sigma_factor    Sigma multiplier for which the crossing rate will be counted
 * @param[in]       stride          Vector element offset stride
 * @param[in, out]  p_ctx           Optional pointer to the statistics context,
 *                                  this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 *
 * @return  neuton_i16_t  Sigma-crossing rate in the vector within a stride, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_scr_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                neuton_dsp_sigma_factor_t sigma_factor, size_t stride,
                                neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Counts Sigma-crossing rate with respect to Mean, of a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   p_ctx     Optional pointer to the statistics context,
 *                        this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 *
 * @return  neuton_i16_t  Sigma-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_scr_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_sigma_factor_t sigma_factor,
                                neuton_dsp_stat_ctx_i16_t* p_ctx);

/**
 * @brief Counts Sigma-crossing rate with respect to Mean, of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]       p_input         Pointer to the input vector
 * @param[in]       num             Number of samples with 'stride' in input vector
 * @param[in]       sigma_factor    Sigma multiplier for which the crossing rate will be counted
 * @param[in]       stride          Vector element offset stride
 * @param[in, out]  p_ctx           Optional pointer to the statistics context,
 *                                  this function will use <pre> p_ctx->value.var </pre> for calculation if it exist
 *
 * @return  neuton_i16_t  Sigma-crossing rate in the vector within a stride, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_scr_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_sigma_factor_t sigma_factor, size_t stride,
                                neuton_dsp_stat_ctx_i16_t* p_ctx);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_SCR_FUNCTIONS_H_ */

/**
 * @}
 */
