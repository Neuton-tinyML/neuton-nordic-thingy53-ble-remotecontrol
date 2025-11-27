/**
 *
 * @defgroup neuton_dsp_spectral_thd Frequency Total Harmonic Distortion
 * @{
 * @ingroup neuton_dsp_spectral
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SPECTRAL_FREQUENCY_THD_H_
#define _NEUTON_DSP_SPECTRAL_FREQUENCY_THD_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compute Total Harmonic Distortion for provided frequency in floating point spectrum
 * 
 * @param[in] p_amplitude_spectrum      Pointer to amplitude spectrum vector
 * @param[in] num                       Number of bins/samples in amplitude spectrum
 * @param[in] base_freq_index           Frequency index(bin) in amplitude spectrum for which THD will be computed
 * @param[in] n_harmonics               Number of harmonics to compute THD, starting from second one, 
 *                                      e.g. n_harmonics = 3 then for THD will be used H_2x, H_3x, H_4x
 *  
 * @return neuton_f32_t Total Harmonic Distortion
 */
neuton_f32_t neuton_dsp_freq_thd_f32(neuton_f32_t p_amplitude_spectrum[],
                                     neuton_u16_t num,
                                     neuton_u16_t base_freq_index,
                                     neuton_u16_t n_harmonics);

/**
 * @brief Compute Total Harmonic Distortion for provided frequency in fixed-point spectrum
 * 
 * @param[in] p_amplitude_spectrum      Pointer to amplitude spectrum vector
 * @param[in] num                       Number of bins/samples in amplitude spectrum
 * @param[in] base_freq_index           Frequency index(bin) in amplitude spectrum for which THD will be computed
 * @param[in] n_harmonics               Number of harmonics to compute THD, starting from second one, 
 *                                      e.g. n_harmonics = 3 then for THD will be used H_2x, H_3x, H_4x
 *  
 * @return neuton_i16_t Relative Total Harmonic Distortion
 */
neuton_i16_t neuton_dsp_freq_thd_i16(neuton_i16_t p_amplitude_spectrum[],
                                     neuton_u16_t num,
                                     neuton_u16_t base_freq_index,
                                     neuton_u16_t n_harmonics);
#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SPECTRAL_FREQUENCY_THD_H_ */

/**
 * @}
 */
