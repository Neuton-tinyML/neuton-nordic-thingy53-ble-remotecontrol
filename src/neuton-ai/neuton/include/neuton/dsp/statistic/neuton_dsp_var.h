/**
 *
 * @defgroup neuton_dsp_statistic_var Variance
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_VAR_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_VAR_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Calculate Variance value of a floating-point vector.
 * @details This function uses internal accumulator of neuton_f32_t size, 
 *          for calculating sum of squares of values, so it will lose precision if
 *          values ​​less than 10e-4
 *
 * @param[in]        p_input   Pointer to the input vector
 * @param[in]        num       Number of samples in input vector
 * @param[in, out]   p_ctx     Optional pointer to the statistics context,
 *                             this function will use <pre> p_ctx->value.sum </pre> for calculation if it exist
 *                             the calculated value of variance will be written to context for further use
 *
 * @return  neuton_f32_t  Variance value of the vector
 */
neuton_f32_t neuton_dsp_var_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Calculate Variance value of a floating-point vector ​​using values ​​in increments of 'stride'.
 * @details This function uses internal accumulator of neuton_f32_t size, 
 *          for calculating sum of squares of values, so it will lose precision if
 *          values ​​less than 10e-4
 *
 * @param[in]        p_input   Pointer to the input vector
 * @param[in]        num       Number of samples with 'stride' in input vector
 * @param[in]        stride    Vector element offset stride
 * @param[in, out]   p_ctx     Optional pointer to the statistics context,
 *                             this function will use <pre> p_ctx->value.sum </pre> for calculation if it exist
 *                             the calculated value of variance will be written to context for further use
 *
 * @return  neuton_f32_t  Variance value of the vector
 */
neuton_f32_t neuton_dsp_var_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Derivatives of variance for floating-point format
 */
typedef struct neuton_dsp_derivative_var_f32_s
{
    /** First Derivative of Variance */
    neuton_f32_t first;

    /** Second Derivative of Variance */
    neuton_f32_t second;
} neuton_dsp_derivative_var_f32_t;

/**
 * @brief Calculate Derivatives of variance in the floating-point vector.
 * @details This function uses internal accumulator of neuton_f32_t size, 
 *          for calculating sum of squares of values, so it will lose precision if
 *          values ​​less than 10e-4
 *
 * @param[in]   p_input            Pointer to the input vector
 * @param[in]   num                Number of samples in input vector
 * @param[out]  p_deriv_variance   Calculated derivatives of variance @ref neuton_dsp_derivative_var_f32_t
 */
void neuton_dsp_deriv_var_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                            neuton_dsp_derivative_var_f32_t* p_deriv_variance);

/**
 * @brief Calculate Variance value of a INT8 fixed-point vector.
 *
 * @param[in]        p_input   Pointer to the input vector
 * @param[in]        num       Number of samples in input vector
 * @param[in, out]   p_ctx     Optional pointer to the statistics context, this function will use
 *                              <pre> p_ctx->value.sum and/or p_ctx->value.tss </pre> for calculation if it exist,
 *                             the calculated value of variance will be written to context for further use
 *
 * @return  neuton_u16_t  Variance value of the vector
 */
neuton_u16_t neuton_dsp_var_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Calculate Variance value of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]       p_input         Pointer to the input vector
 * @param[in]       num             Number of samples with 'stride' in input vector
 * @param[in]       stride          Vector element offset stride
 * @param[in, out]   p_ctx          Optional pointer to the statistics context, this function will use
 *                                   <pre> p_ctx->value.sum and/or p_ctx->value.tss </pre> for calculation if it exist,
 *                                  the calculated value of variance will be written to context for further use
 *
 * @return  neuton_u16_t  Variance value of the vector
 */
neuton_u16_t neuton_dsp_var_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                 size_t stride, neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Derivatives of variance for INT8 format
 */
typedef struct neuton_dsp_derivative_var_i8_s
{
    /** First Derivative of Variance */
    neuton_u16_t first;

    /** Second Derivative of Variance*/
    neuton_u16_t second;
} neuton_dsp_derivative_var_i8_t;

/**
 * @brief Calculate Derivatives of variance in the INT8 fixed-point vector.
 *
 * @param[in]   p_input            Pointer to the input vector
 * @param[in]   num                Number of samples in input vector
 * @param[out]  p_deriv_variance   Calculated derivatives of variance @ref neuton_dsp_derivative_var_i8_t
 */
void neuton_dsp_deriv_var_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                            neuton_dsp_derivative_var_i8_t* p_deriv_variance);

/**
 * @brief Calculate Variance value of a INT16 fixed-point vector.
 *
 * @param[in]        p_input   Pointer to the input vector
 * @param[in]        num       Number of samples in input vector
 * @param[in, out]   p_ctx     Optional pointer to the statistics context, this function will use 
 *                              <pre> p_ctx->value.sum and/or p_ctx->value.tss </pre> for calculation if it exist,
 *                             the calculated value of variance will be written to context for further use
 *
 * @return  neuton_u32_t  Variance value of the vector
 */
neuton_u32_t neuton_dsp_var_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i16_t* p_ctx);

/**
 * @brief Calculate Variance value of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]        p_input         Pointer to the input vector
 * @param[in]        num             Number of samples with 'stride' in input vector
 * @param[in]        stride          Vector element offset stride
 * @param[in, out]   p_ctx           Optional pointer to the statistics context, this function will use
 *                                    <pre> p_ctx->value.sum and/or p_ctx->value.tss </pre> for calculation if it exist,
 *                                   the calculated value of variance will be written to context for further use
 *
 * @return  neuton_u32_t  Variance value of the vector
 */
neuton_u32_t neuton_dsp_var_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                 size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx);

/**
 * @brief Derivatives of variance for INT16 format
 */
typedef struct neuton_dsp_derivative_var_i16_s
{
    /** First Derivative of Variance */
    neuton_u32_t first;

    /** Second Derivative of Variance */
    neuton_u32_t second;
} neuton_dsp_derivative_var_i16_t;

/**
 * @brief Calculate Derivatives of variance in the INT16 fixed-point vector.
 *
 * @param[in]   p_input            Pointer to the input vector
 * @param[in]   num                Number of samples in input vector
 * @param[out]  p_deriv_variance   Calculated derivatives of variance @ref neuton_dsp_derivative_var_i16_t
 */
void neuton_dsp_deriv_var_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                            neuton_dsp_derivative_var_i16_t* p_deriv_variance);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_VAR_FUNCTIONS_H_ */

/**
 * @}
 */
