/**
 *
 * @defgroup neuton_dsp_windowing Windowing functions
 * @{
 * @ingroup neuton_dsp_support
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SUPPORT_WINDOWING_H_
#define _NEUTON_DSP_SUPPORT_WINDOWING_H_

#include <neuton/neuton_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Initialize Hanning window
 * 
 * @param[out]  p_window        Pointer to window for initialization 
 * @param[in]   window_size     Window size in samples
 */
void neuton_dsp_window_hanning_f32(neuton_f32_t* p_window, neuton_u16_t window_size);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SUPPORT_WINDOWING_H_ */

/**
 * @}
 */
