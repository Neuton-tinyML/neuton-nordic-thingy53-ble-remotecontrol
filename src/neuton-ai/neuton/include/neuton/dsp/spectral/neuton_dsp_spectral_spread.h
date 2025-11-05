/**
 *
 * @defgroup neuton_dsp_spectral_centroid Spectral Spread
 * @{
 * @ingroup neuton_dsp_spectral
 *
 * @brief Spectral spreads represent the standard deviation of amplitude distribution around a sound’s spectral centroid, 
 *          calculated using the square root of its second-order moment. 
 *          A signal with a high spectral spread will look “larger” and “flatter” (literally more “spread”) 
 *          than a signal with a lower spectral spread value.
 *
 */
#ifndef _NEUTON_DSP_SPECTRAL_SPREAD_H_
#define _NEUTON_DSP_SPECTRAL_SPREAD_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculate Spectral Spread in floating-point spectrum
 * 
 * @param[in]       p_spectrum            Pointer to amplitude spectrum vector
 * @param[in]       num                   Number of bins/samples in amplitude spectrum
 * @param[in, out]  p_ctx                 Pointer to optional spectral context,
 *                                        the calculated value of magnitude_sum and cetroid will be used
 *  
 * @return neuton_f32_t Spectral Spread
 */
neuton_f32_t neuton_dsp_spectral_spread_f32(neuton_f32_t                   p_spectrum[],
                                            neuton_u16_t                   num,
                                            neuton_dsp_spectral_ctx_f32_t* p_ctx);

/**
 * @brief Calculate Spectral Spread in INT16 fixed-point spectrum
 * 
 * @param[in]       p_spectrum            Pointer to amplitude spectrum vector
 * @param[in]       num                   Number of bins/samples in amplitude spectrum
 * @param[in, out]  p_ctx                 Pointer to optional spectral context,
 *                                        the calculated value of magnitude_sum and cetroid will be used
 *  
 * @return neuton_i16_t Spectral Spread
 */
neuton_i16_t neuton_dsp_spectral_spread_i16(neuton_i16_t                   p_spectrum[],
                                            neuton_u16_t                   num,
                                            neuton_dsp_spectral_ctx_i16_t* p_ctx);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SPECTRAL_SPREAD_H_ */

/**
 * @}
 */
