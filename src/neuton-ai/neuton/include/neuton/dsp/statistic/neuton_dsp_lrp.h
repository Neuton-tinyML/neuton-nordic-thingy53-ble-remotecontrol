/**
 *
 * @defgroup neuton_dsp_statistic_lrp Linear Regression Parameters
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_LRP_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_LRP_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct neuton_dsp_linear_reg_params_f32_s
{
    /* Slope of linear regression */
    neuton_f32_t slope;

    /* Intercept of linear regression */
    neuton_f32_t intercept;
} neuton_dsp_linear_reg_params_f32_t;

typedef struct neuton_dsp_linear_reg_params_i16_s
{
    /* Slope of linear regression */
    neuton_i32_t slope;

    /* Intercept of linear regression */
    neuton_i32_t intercept;
} neuton_dsp_linear_reg_params_i16_t;

typedef struct neuton_dsp_linear_reg_params_i8_s
{
    /* Slope of linear regression */
    neuton_i16_t slope;

    /* Intercept of linear regression */
    neuton_i16_t intercept;
} neuton_dsp_linear_reg_params_i8_t;

/**
 * @brief Calculate Linear Regression Parameters (Slope, Intercept) of a floating-point vector.
 *
 * @param[in]   p_input  Pointer to the input vector
 * @param[in]   num      Number of samples in input vector
 * @param[out]  p_params Calculated Linear Regression Parameters (Slope, Intercept), @ref neuton_dsp_linear_reg_params_f32_t
 * @param[in]   p_ctx    Optional pointer to the statistics context,
 *                       this function will use <pre> p_ctx->value.sum </pre> for calculation if it exist
 */
void neuton_dsp_lrp_f32(const neuton_f32_t*                 p_input,
                        neuton_u16_t                        num,
                        neuton_dsp_linear_reg_params_f32_t* p_params,
                        neuton_dsp_stat_ctx_f32_t*          p_ctx);

/**
 * @brief Calculate Linear Regression Parameters (Slope, Intercept) of a INT16 fixed-point vector.
 *
 * @param[in]  p_input   Pointer to the input vector
 * @param[in]  num       Number of samples in input vector
 * @param[out] p_params  Calculated Linear Regression Parameters (Slope, Intercept), @ref neuton_dsp_linear_reg_params_i16_t 
 * @param[in]  p_ctx     Optional pointer to the statistics context,
 *                       this function will use <pre> p_ctx->value.sum </pre> for calculation if it exist
 *
 */
void neuton_dsp_lrp_i16(const neuton_i16_t*                 p_input,
                        neuton_u16_t                        num,
                        neuton_dsp_linear_reg_params_i16_t* p_params,
                        neuton_dsp_stat_ctx_i16_t*          p_ctx);

void neuton_dsp_lrp_i8(const neuton_i8_t*                 p_input,
                       neuton_u16_t                       num,
                       neuton_dsp_linear_reg_params_i8_t* p_params,
                       neuton_dsp_stat_ctx_i8_t*          p_ctx);
#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_LRP_FUNCTIONS_H_ */

/**
 * @}
 */
