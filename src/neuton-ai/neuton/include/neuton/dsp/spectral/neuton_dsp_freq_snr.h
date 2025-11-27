/**
 *
 * @defgroup neuton_dsp_spectral_thd Frequencies Signal-to-Noise ratio
 * @{
 * @ingroup neuton_dsp_spectral
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SPECTRAL_FREQUENCY_SNR_H_
#define _NEUTON_DSP_SPECTRAL_FREQUENCY_SNR_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compute signal-to-noise ratio for provided frequencies in floating-point amplitude spectrum,
 *           signal represent provided frequencies, noise is everything else
 * 
 * @param[in] p_amplitude_spectrum      Pointer to amplitude spectrum vector
 * @param[in] num                       Number of bins/samples in amplitude spectrum
 * @param[in] p_freq_indicies           Pointer to frequency indicies (bins) for which SNR will be computed
 * @param[in] freq_indicies_num         Number of frequency indicies provided
 *  
 * @return neuton_i16_t SNR of provided frequencies 
 */
neuton_f32_t neuton_dsp_freq_snr_f32(neuton_f32_t p_amplitude_spectrum[],
                                     neuton_u16_t num,
                                     neuton_u16_t p_freq_indicies[],
                                     neuton_u16_t freq_indicies_num);

/**
 * @brief Compute signal-to-noise ratio for provided frequencies in fixed-point amplitude spectrum,
 *           signal represent provided frequencies, noise is everything else
 * 
 * @param[in] p_amplitude_spectrum      Pointer to amplitude spectrum vector
 * @param[in] num                       Number of bins/samples in amplitude spectrum
 * @param[in] p_freq_indicies           Pointer to frequency indicies (bins) for which SNR will be computed
 * @param[in] freq_indicies_num         Number of frequency indicies provided
 *  
 * @return neuton_i16_t SNR of provided frequencies 
 */
neuton_i16_t neuton_dsp_freq_snr_i16(neuton_i16_t p_amplitude_spectrum[],
                                     neuton_u16_t num,
                                     neuton_u16_t p_freq_indicies[],
                                     neuton_u16_t freq_indicies_num);
#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SPECTRAL_FREQUENCY_SNR_H_ */

/**
 * @}
 */
