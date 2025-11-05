/**
 *
 * @defgroup neuton_dsp_statistic_absmin Absolute Minimum
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_ABSMIN_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_ABSMIN_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Finds Absolute Minimum value of a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_f32_t  Absolute Minimum value in the vector
 */
neuton_f32_t neuton_dsp_absmin_f32(const neuton_f32_t* p_input, neuton_u16_t num);

/**
 * @brief Finds Absolute Minimum value of a floating-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_f32_t  Absolute Minimum value in the vector
 */
neuton_f32_t neuton_dsp_absmin_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                                    size_t stride);

/**
 * @brief Finds Absolute Minimum value of a INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i8_t  Absolute Minimum value in the vector
 */
neuton_i8_t neuton_dsp_absmin_i8(const neuton_i8_t* p_input, neuton_u16_t num);

/**
 * @brief Finds Absolute Minimum value of a INT8 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i8_t  Absolute Minimum value in the vector
 */
neuton_i8_t neuton_dsp_absmin_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                    size_t stride);

/**
 * @brief Finds Absolute Minimum value of a INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i16_t  Absolute Minimum value in the vector
 */
neuton_i16_t neuton_dsp_absmin_i16(const neuton_i16_t* p_input, neuton_u16_t num);

/**
 * @brief Finds Absolute Minimum value of a INT16 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Absolute Minimum value in the vector
 */
neuton_i16_t neuton_dsp_absmin_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                    size_t stride);

/**
 * @brief Finds Absolute Minimum value of a INT32 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *
 * @return  neuton_i32_t  Absolute Minimum value in the vector
 */
neuton_i32_t neuton_dsp_absmin_i32(const neuton_i32_t* p_input, neuton_u16_t num);

/**
 * @brief Finds Absolute Minimum value of a INT32 fixed-point vector ​​using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples with 'stride' in input vector
 * @param[in]   stride    Vector element offset stride
 *
 * @return  neuton_i16_t  Absolute Minimum value in the vector
 */
neuton_i32_t neuton_dsp_absmin_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                    size_t stride);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_ABSMIN_FUNCTIONS_H_ */

/**
 * @}
 */
