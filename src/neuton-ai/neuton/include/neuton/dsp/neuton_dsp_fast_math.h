/**
 *
 * @defgroup neuton_dsp_fast_math Fast Math
 * @{
 * @ingroup neuton_dsp
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_FAST_MATH_FUNCTIONS_H_
#define _NEUTON_DSP_FAST_MATH_FUNCTIONS_H_

#include "fast_math/neuton_dsp_cmplx_math.h"

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Calculate square root of the provided floating point value 
 * 
 * @param[in] x             Argument for square root calculation 
 * 
 * @return neuton_f32_t     Square root of the provided argument
 */
neuton_f32_t neuton_dsp_sqrt_f32(const neuton_f32_t x);

/**
 * @brief Calculate square root of the provided UINT32 value 
 * 
 * @param[in] x             Argument for square root calculation 
 * 
 * @return neuton_u32_t     Square root of the provided argument
 */
neuton_u32_t neuton_dsp_sqrt_u32(const neuton_u32_t x);



#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_FAST_MATH_FUNCTIONS_H_ */

/**
 * @}
 */
