/**
 *
 * @defgroup neuton_dsp_statistic_moments Statistical Moments
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_MOMENTS_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_MOMENTS_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief  Floating-point statistical moments container
 */
typedef union neuton_dsp_moments_f32_u
{
    struct
    {
        /** Variance */
        neuton_f32_t var;
        /** Skewness */
        neuton_f32_t skew;
        /** Excess Kurtosis */
        neuton_f32_t kur;
    } moment;
    
    neuton_f32_t moments[3U];
} neuton_dsp_moments_f32_t;

/**
 * @brief INT8 statistical moments container
 */
typedef union neuton_dsp_moments_i8_u
{
    struct
    {
        /** Variance */
        neuton_i16_t var;
        /** Skewness in custom integer format with high float correlation */
        neuton_i16_t skew;
        /** Kurtosis in custom integer format with high float correlation */
        neuton_i16_t kur;
    } moment;
    
    neuton_i16_t moments[3U];
} neuton_dsp_moments_i8_t;

/**
 * @brief INT16 statistical moments container
 */
typedef union neuton_dsp_moments_i16_u
{
    struct
    {
        /** Variance */
        neuton_i32_t var;
        /** Skewness in custom integer format with high float correlation */
        neuton_i32_t skew;
        /** Kurtosis in custom integer format with high float correlation */
        neuton_i32_t kur;
    } moment;
    
    neuton_i32_t moments[3U];
} neuton_dsp_moments_i16_t;

/**
 * @brief Calculate 3 higher statistical moments(Variance, Skewness, Kurtosis) of a floating-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[in, out]  p_ctx     Optional pointer to the statistics context, this function will use
 *                            <pre> p_ctx->value.sum and/or p_ctx->value.var </pre> for calculation if it exist,
 *                            the calculated value of variance will be written to context for further use
 * @param[out]      p_m       Pointer to the moments container @ref neuton_dsp_moments_f32_t
 */
void neuton_dsp_moments_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                            neuton_dsp_stat_ctx_f32_t* p_ctx, neuton_dsp_moments_f32_t* p_m);

/**
 * @brief Calculate 3 higher statistical moments(Variance, Skewness, Kurtosis) of a floating-point vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples with 'stride' in input vector
 * @param[in]       stride    Vector element offset stride
 * @param[in, out]  p_ctx     Optional pointer to the statistics context, this function will use
 *                            <pre> p_ctx->value.sum and/or p_ctx->value.var </pre> for calculation if it exist,
 *                            the calculated value of variance will be written to context for further use
 * @param[out]      p_m       Pointer to the moments container @ref neuton_dsp_moments_f32_t
 */
void neuton_dsp_moments_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, size_t stride,
                            neuton_dsp_stat_ctx_f32_t* p_ctx, neuton_dsp_moments_f32_t* p_m);

/**
 * @brief Calculate 3 higher statistical moments(Variance, Skewness, Kurtosis) of a INT8 vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[in, out]  p_ctx     Optional pointer to the statistics context, this function will use
 *                            <pre> p_ctx->value.sum and/or p_ctx->value.var </pre> for calculation if it exist,
 *                            the calculated value of variance will be written to context for further use
 * @param[out]      p_m       Pointer to the moments container @ref neuton_dsp_moments_i8_t
 */
void neuton_dsp_moments_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                            neuton_dsp_stat_ctx_i8_t* p_ctx, neuton_dsp_moments_i8_t* p_m);

/**
 * @brief Calculate 3 higher statistical moments(Variance, Skewness, Kurtosis) of a INT16 vector.
 *
 * @param[in]       p_input   Pointer to the input vector
 * @param[in]       num       Number of samples in input vector
 * @param[in, out]  p_ctx     Optional pointer to the statistics context, this function will use
 *                            <pre> p_ctx->value.sum and/or p_ctx->value.var </pre> for calculation if it exist,
 *                            the calculated value of variance will be written to context for further use
 * @param[out]      p_m       Pointer to the moments container @ref neuton_dsp_moments_i16_t
 */
void neuton_dsp_moments_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                            neuton_dsp_stat_ctx_i16_t* p_ctx, neuton_dsp_moments_i16_t* p_m);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_MOMENTS_FUNCTIONS_H_ */

/**
 * @}
 */
