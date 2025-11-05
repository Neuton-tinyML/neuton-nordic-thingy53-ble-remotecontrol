/**
 *
 * @defgroup neuton_dsp_transform_melspec Mel-Spectrogram
 * @{
 * @ingroup neuton_dsp_transform
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_TRANSFORM_MELSPECTROGRAM_H_
#define _NEUTON_DSP_TRANSFORM_MELSPECTROGRAM_H_

#include <neuton/dsp/neuton_dsp_types.h>
#include "neuton_dsp_rfht.h"

#ifdef   __cplusplus
extern "C"
{
#endif

/** @brief Structure descibing mel-spectrogram preprocessing block */
typedef struct
{
    /** Buffer to store mel-spectrogram 
     * (elements count is @mel_spectrum_n_mels * @mel_spectrum_count)
     */
    neuton_f32_t* p_melspectrum;

    /** FHT instance */
    neuton_dsp_rfht_instance_t fht;

    /** Sample rate of audio signal */
    neuton_u16_t sample_rate;

    /** Current spectrogram fill */
    neuton_u16_t current_fill;
    
    /** Count of frequency bins */
    neuton_u16_t freq_bands;

    /** Spectrogram Time Bands dim */
    neuton_u16_t time_bands;
} neuton_dsp_melspectr_ctx_f32_t;

/**
 * @brief Make mel-spectrogram from timeseries audio data
 * 
 * @param[in] p_ctx            Pointer to mel-spectrogram instance
 * @param[in] p_audio_input    Audio input to process
 * 
 * @return neuton_i8_t      Return 0 if spectrogram is ready, otherwise 1
 */
neuton_i8_t neuton_dsp_melspectr_make_f32(neuton_dsp_melspectr_ctx_f32_t* p_ctx, 
                                        neuton_f32_t* p_audio_input);

/**
 * @brief Shift mel-spectrogram to the right on N columns
 * 
 * @param[in] p_ctx        Pointer to mel-spectrogram instance
 * @param[in] shift        Number of spectrograms to shift
 */
void neuton_dsp_melspectr_shift_f32(neuton_dsp_melspectr_ctx_f32_t* p_ctx, 
                                    neuton_u16_t shift);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_TRANSFORM_MELSPECTROGRAM_H_ */

/**
 * @}
 */
