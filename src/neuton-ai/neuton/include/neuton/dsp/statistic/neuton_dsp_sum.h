/**
 *
 * @defgroup neuton_dsp_statistic_sum Sum
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_SUM_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_SUM_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif


/**
 * @brief Calculate Sum of values of a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_f32_t  Sum value of the vector
 */
neuton_f32_t neuton_dsp_sum_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Calculate Sum value of a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_f32_t  Sum value of the vector
 */
neuton_f32_t neuton_dsp_sum_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                    size_t stride, neuton_dsp_stat_ctx_f32_t* p_ctx);

/**
 * @brief Calculate Sum value of a INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_i32_t  Sum value of the vector
 */
neuton_i32_t neuton_dsp_sum_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Calculate Sum value of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_i32_t  Sum value of the vector
 */
neuton_i32_t neuton_dsp_sum_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_i8_t* p_ctx);

/**
 * @brief Calculate Sum value of a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_i32_t  Sum value of the vector
 */
neuton_i32_t neuton_dsp_sum_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i16_t* p_ctx);

/**
 * @brief Calculate Sum value of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_i32_t  Sum value of the vector
 */
neuton_i32_t neuton_dsp_sum_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_i16_t* p_ctx);

/**
 * @brief Calculate Sum value of a INT32 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_i64_t  Sum value of the vector
 */
neuton_i64_t neuton_dsp_sum_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                neuton_dsp_stat_ctx_i32_t* p_ctx);

/**
 * @brief Calculate Sum value of a INT32 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[out]  p_ctx     Optional pointer to the statistics context,
 *                        the calculated value of sum will be written to context for further use
 *
 * @return  neuton_i64_t  Sum value of the vector
 */
neuton_i64_t neuton_dsp_sum_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                size_t stride, neuton_dsp_stat_ctx_i32_t* p_ctx);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_SUM_FUNCTIONS_H_ */

/**
 * @}
 */
