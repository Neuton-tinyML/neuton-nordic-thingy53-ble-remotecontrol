/**
 *
 * @defgroup neuton_dsp_statistic_psot Percentage of signal over threshold
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_PSOT_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_PSOT_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Calculates Percentage of signal over threshold in a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   threshold Threshold value for counting percentage of signal over this value
 *
 * @return  neuton_f32_t  Percentage of signal over threshold in the vector
 */
neuton_f32_t neuton_dsp_psot_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                const neuton_f32_t threshold);

/**
 * @brief Calculates Percentage of signal over threshold in a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[in]   threshold Threshold value for counting percentage of signal over this value
 *
 * @return  neuton_f32_t  Percentage of signal over threshold in the vector
 */
neuton_f32_t neuton_dsp_psot_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                size_t stride, const neuton_f32_t threshold);

/**
 * @brief Calculates Percentage of signal over threshold in a INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   threshold Threshold value for counting percentage of signal over this value
 *
 * @return  neuton_i16_t  Percentage of signal over threshold in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_psot_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                const neuton_i8_t threshold);

/**
 * @brief Calculates Percentage of signal over threshold in a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[in]   threshold Threshold value for counting percentage of signal over this value
 *
 * @return  neuton_i16_t  Percentage of signal over threshold in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_psot_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride, const neuton_i8_t threshold);

/**
 * @brief Calculates Percentage of signal over threshold in a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   threshold Threshold value for counting percentage of signal over this value
 *
 * @return  neuton_i16_t  Percentage of signal over threshold in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_psot_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                 const neuton_i16_t threshold);

/**
 * @brief Calculates Percentage of signal over threshold in a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[in]   threshold Threshold value for counting percentage of signal over this value
 *
 * @return  neuton_i16_t  Percentage of signal over threshold in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_psot_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride, const neuton_i16_t threshold);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_PSOT_FUNCTIONS_H_ */

/**
 * @}
 */
