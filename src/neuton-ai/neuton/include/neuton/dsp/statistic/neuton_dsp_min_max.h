/**
 *
 * @defgroup neuton_dsp_statistic_min_max Minimum and Maximum
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_MIN_MAX_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_MIN_MAX_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Finds Maximum and Minimum value of a floating-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_min     Pointer to store Minimum value in the vector
 * @param[out]  p_max     Pointer to store Maximum value in the vector
 *
 */
void neuton_dsp_min_max_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                            neuton_f32_t* p_min, neuton_f32_t* p_max);

/**
 * @brief Finds Maximum and Minimum value of a floating-point vector using values 
 *          ​​in increments of 'stride'.
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples with 'stride' in input vector
 * @param[in]  stride       Vector element offset stride
 * @param[out] p_min        Pointer to store Minimum value in the vector 
 * @param[out] p_max        Pointer to store Maximum value in the vector 
 */
void neuton_dsp_min_max_f32_s(const neuton_f32_t* p_input, neuton_u16_t num, 
                            size_t stride,
                            neuton_f32_t* p_min, neuton_f32_t* p_max);

/**
 * @brief Finds Maximum and Minimum value of INT8 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_min     Pointer to store Minimum value in the vector
 * @param[out]  p_max     Pointer to store Maximum value in the vector
 *
 */
void neuton_dsp_min_max_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                            neuton_i8_t* p_min, neuton_i8_t* p_max);

/**
 * @brief Finds Maximum and Minimum value of a INT8 fixed-point vector using values 
 *          ​​in increments of 'stride'.
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples with 'stride' in input vector
 * @param[in]  stride       Vector element offset stride
 * @param[out] p_min        Pointer to store Minimum value in the vector 
 * @param[out] p_max        Pointer to store Maximum value in the vector 
 */
void neuton_dsp_min_max_i8_s(const neuton_i8_t* p_input, neuton_u16_t num, 
                            size_t stride,
                            neuton_i8_t* p_min, neuton_i8_t* p_max);

/**
 * @brief Finds Maximum and Minimum value of INT16 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_min     Pointer to store Minimum value in the vector
 * @param[out]  p_max     Pointer to store Maximum value in the vector
 *
 */
void neuton_dsp_min_max_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                            neuton_i16_t* p_min, neuton_i16_t* p_max);

/**
 * @brief Finds Maximum and Minimum value of a INT16 fixed-point vector using values 
 *          ​​in increments of 'stride'.
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples with 'stride' in input vector
 * @param[in]  stride       Vector element offset stride
 * @param[out] p_min        Pointer to store Minimum value in the vector 
 * @param[out] p_max        Pointer to store Maximum value in the vector 
 */
void neuton_dsp_min_max_i16_s(const neuton_i16_t* p_input, neuton_u16_t num, 
                              size_t stride,
                              neuton_i16_t* p_min, neuton_i16_t* p_max);

/**
 * @brief Finds Maximum and Minimum value of INT32 fixed-point vector.
 *
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[out]  p_min     Pointer to store Minimum value in the vector
 * @param[out]  p_max     Pointer to store Maximum value in the vector
 *
 */
void neuton_dsp_min_max_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                            neuton_i32_t* p_min, neuton_i32_t* p_max);

/**
 * @brief Finds Maximum and Minimum value of a INT32 fixed-point vector using values 
 *          ​​in increments of 'stride'.
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples with 'stride' in input vector
 * @param[in]  stride       Vector element offset stride
 * @param[out] p_min        Pointer to store Minimum value in the vector 
 * @param[out] p_max        Pointer to store Maximum value in the vector 
 */
void neuton_dsp_min_max_i32_s(const neuton_i32_t* p_input, neuton_u16_t num, 
                              size_t stride,
                              neuton_i32_t* p_min, neuton_i32_t* p_max);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_MIN_MAX_FUNCTIONS_H_ */

/**
 * @}
 */
