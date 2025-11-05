/**
 *
 * @defgroup neuton_dsp_clip Clipping
 * @{
 * @ingroup neuton_dsp_support
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SUPPORT_CLIPPING_H_
#define _NEUTON_DSP_SUPPORT_CLIPPING_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Clips floating-point values to the limit (min, max)
 * 
 * @param[in, out] p_input  Pointer to the input vector
 * @param[in]      num      Number of samples in the input vector
 * @param[in]      min      Minimum limit for the input samples, all value below will be clipped to this limit
 * @param[in]      max      Maximum limit for the input samples, all value above will be clipped to this limit
 */
void neuton_dsp_clip_f32(neuton_f32_t*      p_input,
                         neuton_u16_t       num,
                         const neuton_f32_t min,
                         const neuton_f32_t max);

/**
 * @brief Clips INT8 values to the limit (min, max)
 * 
 * @param[in, out] p_input  Pointer to the input vector
 * @param[in]      num      Number of samples in the input vector
 * @param[in]      min      Minimum limit for the input samples, all value below will be clipped to this limit
 * @param[in]      max      Maximum limit for the input samples, all value above will be clipped to this limit
 */
void neuton_dsp_clip_i8(neuton_i8_t*      p_input,
                        neuton_u16_t      num,
                        const neuton_i8_t min,
                        const neuton_i8_t max);

/**
 * @brief Clips INT16 values to the limit (min, max)
 * 
 * @param[in, out] p_input  Pointer to the input vector
 * @param[in]      num      Number of samples in the input vector
 * @param[in]      min      Minimum limit for the input samples, all value below will be clipped to this limit
 * @param[in]      max      Maximum limit for the input samples, all value above will be clipped to this limit
 */
void neuton_dsp_clip_i16(neuton_i16_t*      p_input,
                         neuton_u16_t       num,
                         const neuton_i16_t min,
                         const neuton_i16_t max);

/** @def neuton_dsp_clip
 *
 * @brief Macro for clipping variable to the limit (min, max). 
 * 
 * @param[in] input    Variable for clipping
 * @param[in] min      Minimum limit for the variable, value below will be clipped to this limit
 * @param[in] max      Maximum limit for the variable, value above will be clipped to this limit
 * 
 * @return Clipped variable
 */
#define neuton_dsp_clip(input, min, max) \
    (((input) < (min)) ? (min) : (((input) > (max)) ? (max) : (input)))

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SUPPORT_CLIPPING_H_ */

/**
 * @}
 */
