/**
 *
 * @defgroup neuton_dsp_statistic_tcr Threshold-crossing Rate
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_TCR_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_TCR_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Counts Threshold-crossing rate of a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_f32_t  Threshold-crossing rate in the vector
 */
neuton_f32_t neuton_dsp_tcr_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                const neuton_f32_t threshold);

/**
 * @brief Counts Threshold-crossing rate of a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_f32_t  Threshold-crossing rate in the vector
 */
neuton_f32_t neuton_dsp_tcr_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                size_t stride, const neuton_f32_t threshold);

/**
 * @brief Counts Threshold-crossing rate of a INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_i16_t  Threshold-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_tcr_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                const neuton_i8_t threshold);

/**
 * @brief Counts Threshold-crossing rate of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_i16_t  Threshold-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_tcr_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride, const neuton_i8_t threshold);

/**
 * @brief Counts Threshold-crossing rate of a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_i16_t  Threshold-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_tcr_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                 const neuton_i16_t threshold);

/**
 * @brief Counts Threshold-crossing rate of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_i16_t  Threshold-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_tcr_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride, const neuton_i16_t threshold);

/**
 * @brief Counts Threshold-crossing rate of a INT32 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_i16_t  Threshold-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_tcr_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                const neuton_i32_t threshold);

/**
 * @brief Counts Threshold-crossing rate of a INT32 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 * @param[in]   threshold Threshold value for counting crossing rate
 *
 * @return  neuton_i16_t  Threshold-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_tcr_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                size_t stride, const neuton_i32_t threshold);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_TCR_FUNCTIONS_H_ */

/**
 * @}
 */
