/**
 *
 * @defgroup neuton_dsp_cmplx_math Complex math functions
 * @{
 * @ingroup neuton_dsp_fast_math
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_FASTMATH_COMPLEX_MATH_H_
#define _NEUTON_DSP_FASTMATH_COMPLEX_MATH_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Computes the magnitude of the elements of a complex data vector.
 * 
 * @param[in]   p_input          Input array and the data is stored in an interleaved fashion [xR0, xI0, xR1, xI1, ..., xRn, xIn].
 *                               The input array should has a total of <code>2*num</code> values
 * @param[out]  p_output         Output array where results should be written.
 *                               The output array should has len of <code>num</code> samples
 * @param[in]   num              The number of complex samples in the input array
 */
void neuton_dsp_cmplx_mag_f32(const neuton_f32_t* p_input,
                              neuton_f32_t*       p_output,
                              neuton_u16_t        num);

/**
 * @brief   Computes the magnitude of the elements of a complex data vector in ingeter 16-bit format.
 * 
 * @param[in]   p_input          Input array and the data is stored in an interleaved fashion [xR0, xI0, xR1, xI1, ..., xRn, xIn].
 *                               The input array should has a total of <code>2*num</code> values
 * @param[out]  p_output         Output array where results should be written.
 *                               The output array should has len of <code>num</code> samples
 * @param[in]   num              The number of complex samples in the input array
 */
void neuton_dsp_cmplx_mag_i16(const neuton_i16_t* p_input,
                              neuton_i16_t*       p_output,
                              neuton_u16_t        num);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_FASTMATH_COMPLEX_MATH_H_ */

/**
 * @}
 */
