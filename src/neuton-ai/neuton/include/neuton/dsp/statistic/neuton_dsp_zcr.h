/**
 *
 * @defgroup neuton_dsp_statistic_zcr Zero-crossing Rate
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_ZCR_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_ZCR_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Counts Zero-crossing rate of a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_f32_t  Zero-crossing rate in the vector
 */
neuton_f32_t neuton_dsp_zcr_f32(const neuton_f32_t* p_input, neuton_u16_t num);

/**
 * @brief Counts Zero-crossing rate of a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_f32_t  Zero-crossing rate in the vector
 */
neuton_f32_t neuton_dsp_zcr_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                size_t stride);

/**
 * @brief Counts Zero-crossing rate of a INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i16_t  Zero-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_zcr_i8(const neuton_i8_t* p_input, neuton_u16_t num);

/**
 * @brief Counts Zero-crossing rate of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Zero-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_zcr_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride);

/**
 * @brief Counts Zero-crossing rate of a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i16_t  Zero-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_zcr_i16(const neuton_i16_t* p_input, neuton_u16_t num);

/**
 * @brief Counts Zero-crossing rate of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Zero-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_zcr_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride);

/**
 * @brief Counts Zero-crossing rate of a INT32 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i16_t  Zero-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_zcr_i32(const neuton_i32_t* p_input, neuton_u16_t num);

/**
 * @brief Counts Zero-crossing rate of a INT32 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Zero-crossing rate in the vector, multiplied by NEUTON_PERCENTAGE_TO_INT_FACTOR
 */
neuton_i16_t neuton_dsp_zcr_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                size_t stride);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_ZCR_FUNCTIONS_H_ */

/**
 * @}
 */
