/**
 *
 * @defgroup neuton_dsp_statistic_madf Mean Absolute Difference
 * @{
 * @ingroup neuton_dsp_statistic
 *
 *
 */
#ifndef _NEUTON_DSP_STAT_MEAN_ABS_DIFF_H_
#define _NEUTON_DSP_STAT_MEAN_ABS_DIFF_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates Mean Absolute Difference value of a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_f32_t  Mean Absolute Difference value in the vector
 */
neuton_f32_t neuton_dsp_madf_f32(const neuton_f32_t* p_input, neuton_u16_t num);

/**
 * @brief Calculates Mean Absolute Difference value of a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_f32_t  Mean Absolute Difference value in the vector
 */
neuton_f32_t neuton_dsp_madf_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, size_t stride);

/**
 * @brief Calculates Mean Absolute Difference value of a INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i16_t  Mean Absolute Difference value in the vector
 */
neuton_i16_t neuton_dsp_madf_i8(const neuton_i8_t* p_input, neuton_u16_t num);

/**
 * @brief Calculates Mean Absolute Difference value of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Mean Absolute Difference value in the vector
 */
neuton_i16_t neuton_dsp_madf_i8_s(const neuton_i8_t* p_input, neuton_u16_t num, size_t stride);

/**
 * @brief Calculates Mean Absolute Difference value of a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i16_t  Mean Absolute Difference value in the vector
 */
neuton_i16_t neuton_dsp_madf_i16(const neuton_i16_t* p_input, neuton_u16_t num);

/**
 * @brief Calculates Mean Absolute Difference value of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Mean Absolute Difference value in the vector
 */
neuton_i16_t neuton_dsp_madf_i16_s(const neuton_i16_t* p_input, neuton_u16_t num, size_t stride);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_MEAN_ABS_DIFF_H_ */

/**
 * @}
 */
