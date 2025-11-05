/**
 *
 * @defgroup neuton_dsp_support_q Quantization
 * @{
 * @ingroup neuton_dsp_support
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SUPPORT_QUANTIZATION_H_
#define _NEUTON_DSP_SUPPORT_QUANTIZATION_H_

#ifdef   __cplusplus
extern "C"
{
#endif

#include <neuton/neuton_types.h>

/**
 * @brief Quantize the elements of the floating-point vector to INT8 vector.
 * 
 * @par Scaling and Overflow Behavior:
 *      The function uses saturating arithmetic.
 *      Results outside of the allowable INT8 range [0x80 0x7F] will be saturated.
 *
 * @note
 *      In order to apply rounding, the library should be rebuilt with the NEUTON_USE_MATH_ROUNDING macro
 * 
 * @param[in]  p_input  Points to the floating-point input vector
 * @param[out] p_out    Points to the INT8 output vector
 * @param[in]  num      Number of samples in input and output vector
 *
 */
void neuton_dsp_quantize_f32_to_i8(const neuton_f32_t* p_input,
                                    neuton_i8_t* p_out,
                                    neuton_u16_t num);

/**
 * @brief Quantize the elements of the floating-point vector to INT16 vector.
 * 
 * @par Scaling and Overflow Behavior
 *      The function uses saturating arithmetic.
 *      Results outside of the allowable INT16 range [0x8000 0x7FFF] are saturated.
 *
 * @note
 *       In order to apply rounding, the library should be rebuilt with the NEUTON_USE_MATH_ROUNDING macro
 * 
 * @param[in]     p_input   Points to the floating-point input vector
 * @param[out]    p_out     Points to the INT16 output vector
 * @param[in]     num       Number of samples in each vector
 *
 */
void neuton_dsp_quantize_f32_to_i16(const neuton_f32_t* p_input,
                                    neuton_i16_t* p_out,
                                    neuton_u16_t num);

/**
 * @brief Quantize the elements of the floating-point vector to INT32 vector.
 * 
 * @par Scaling and Overflow Behavior
 *      The function uses saturating arithmetic.
 *      Results outside of the allowable INT32 range[0x80000000 0x7FFFFFFF] are saturated.
 *
 * @note
 *       In order to apply rounding, the library should be rebuilt with the NEUTON_USE_MATH_ROUNDING macro
 * 
 * @param[in]     p_input   Points to the floating-point input vector
 * @param[out]    p_out     Points to the INT32 output vector
 * @param[in]     num       Number of samples in each vector
 *
 */
void neuton_dsp_quantize_f32_to_i32(const neuton_f32_t* p_input,
                                    neuton_i32_t* p_out,
                                    neuton_u16_t num);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SUPPORT_QUANTIZATION_H_ */

/**
 * @}
 */
