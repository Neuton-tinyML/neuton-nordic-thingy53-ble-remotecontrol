/**
 *
 * @defgroup neuton_dsp_statistic_rds Root Difference Square
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief Root Difference Square is also used as an estimate for a time series complexity 
 *        (A more complex time series has more peaks, valleys etc.).
 *
 */
#ifndef _NEUTON_DSP_STAT_RDS_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_RDS_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Calculates Root Difference Square value of a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_f32_t  Root Difference Square value in the vector
 */
neuton_f32_t neuton_dsp_rds_f32(const neuton_f32_t* p_input, neuton_u16_t num);

/**
 * @brief Calculates Root Difference Square value of a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_f32_t  Root Difference Square value in the vector
 */
neuton_f32_t neuton_dsp_rds_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                    size_t stride);

/**
 * @brief Calculates Root Difference Square value of a INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i16_t  Root Difference Square value in the vector
 */
neuton_i16_t neuton_dsp_rds_i8(const neuton_i8_t* p_input, neuton_u16_t num);

/**
 * @brief Calculates Root Difference Square value of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Root Difference Square value in the vector
 */
neuton_i16_t neuton_dsp_rds_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                    size_t stride);

/**
 * @brief Calculates Root Difference Square value of a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i32_t  Root Difference Square value in the vector
 */
neuton_i32_t neuton_dsp_rds_i16(const neuton_i16_t* p_input, neuton_u16_t num);

/**
 * @brief Calculates Root Difference Square value of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i32_t  Root Difference Square value in the vector
 */
neuton_i32_t neuton_dsp_rds_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                    size_t stride);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_RDS_FUNCTIONS_H_ */

/**
 * @}
 */
