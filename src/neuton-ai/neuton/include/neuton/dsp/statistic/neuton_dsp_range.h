/**
 *
 * @defgroup neuton_dsp_statistic_range Range
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_RANGE_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_RANGE_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the floating point vector.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_f32().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *  
 * @return neuton_f32_t Difference between the minimum and maximum value in the input vector
 */
neuton_f32_t neuton_dsp_range_f32(const neuton_f32_t* p_input, neuton_u16_t num);

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the floating point vector using values in increments of 'stride'.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_f32_s().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   stride    Vector element offset stride
 *  
 * @return neuton_f32_t Difference between the minimum and maximum value in the input vector
 */
neuton_f32_t neuton_dsp_range_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                    size_t stride);

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the INT8 fixed-point vector.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_i8().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *  
 * @return neuton_u8_t Difference between the minimum and maximum value in the input vector
 */
neuton_u8_t neuton_dsp_range_i8(const neuton_i8_t* p_input, neuton_u16_t num);

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the INT8 fixed-point vector using values in increments of 'stride'.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_i8_s().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   stride    Vector element offset stride
 *  
 * @return neuton_u8_t Difference between the minimum and maximum value in the input vector
 */
neuton_u8_t neuton_dsp_range_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                    size_t stride);

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the INT16 fixed-point vector.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_i16().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *  
 * @return neuton_u16_t Difference between the minimum and maximum value in the input vector
 */
neuton_u16_t neuton_dsp_range_i16(const neuton_i16_t* p_input, neuton_u16_t num);

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the INT16 fixed-point vector using values in increments of 'stride'.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_i16_s().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   stride    Vector element offset stride
 *  
 * @return neuton_u16_t Difference between the minimum and maximum value in the input vector
 */
neuton_u16_t neuton_dsp_range_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                    size_t stride);

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the INT32 fixed-point vector.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_i32().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 *  
 * @return neuton_u32_t Difference between the minimum and maximum value in the input vector
 */
neuton_u32_t neuton_dsp_range_i32(const neuton_i32_t* p_input, neuton_u16_t num);

/**
 * @brief Finds the difference between the minimum and maximum value
 *        in the INT32 fixed-point vector using values in increments of 'stride'.
 * @details This function finds min/max values via a call to @ref neuton_dsp_min_max_i32_s().
 * 
 * @param[in]   p_input   Pointer to the input vector
 * @param[in]   num       Number of samples in input vector
 * @param[in]   stride    Vector element offset stride
 *  
 * @return neuton_u32_t Difference between the minimum and maximum value in the input vector
 */
neuton_u32_t neuton_dsp_range_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                    size_t stride);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_RANGE_FUNCTIONS_H_ */

/**
 * @}
 */
