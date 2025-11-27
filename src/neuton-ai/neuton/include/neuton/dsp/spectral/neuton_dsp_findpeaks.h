/**
 *
 * @defgroup neuton_dsp_spectral_findpeaks Find Peaks
 * @{
 * @ingroup neuton_dsp_spectral
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SPECTRAL_FINDPEAKS_H_
#define _NEUTON_DSP_SPECTRAL_FINDPEAKS_H_

#include <neuton/common/neuton_platform.h>
#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Finds peaks indexes in the floating-point vector
 * 
 * @param[in] p_input           Pointer to the input vector
 * @param[in] num               Number of samples in the input vector
 * @param[in] min_peak_height   Minimum peak height to find
 * @param[in] min_peak_distance Minimum distance between peaks 
 * @param[out] peaks_indices    Pointer to the output array with founded highest peak indicies, 
 *                              if peaks corresponding search coniditions (min_peak_height, min_peak_distance) was not found, 
 *                              -1 will be written as output
 * @param[in] peaks_indices_num Number of highest peaks to find
 */
void neuton_dsp_findpeaks_f32(neuton_f32_t p_input[],
                              neuton_u16_t num,
                              neuton_f32_t min_peak_height,
                              neuton_u16_t min_peak_distance,
                              neuton_i16_t peaks_indices[],
                              neuton_u16_t peaks_indices_num);

/**
 * @brief Finds peaks indexes in the INT8 fixed-point
 * 
 * @param[in] p_input           Pointer to the input vector
 * @param[in] num               Number of samples in the input vector
 * @param[in] min_peak_height   Minimum peak height to find
 * @param[in] min_peak_distance Minimum distance between peaks 
 * @param[out] peaks_indices    Pointer to the output array with founded highest peak indicies, 
 *                              if peaks corresponding search coniditions (min_peak_height, min_peak_distance) was not found, 
 *                              -1 will be written as output
 * @param[in] peaks_indices_num Number of highest peaks to find
 */
void neuton_dsp_findpeaks_i8(neuton_i8_t  p_input[],
                             neuton_u16_t num,
                             neuton_i8_t  min_peak_height,
                             neuton_u16_t min_peak_distance,
                             neuton_i16_t peaks_indices[],
                             neuton_u16_t peaks_indices_num);

/**
 * @brief Finds peaks indexes in the INT16 fixed-point
 * 
 * @param[in] p_input           Pointer to the input vector
 * @param[in] num               Number of samples in the input vector
 * @param[in] min_peak_height   Minimum peak height to find
 * @param[in] min_peak_distance Minimum distance between peaks 
 * @param[out] peaks_indices    Pointer to the output array with founded highest peak indicies, 
 *                              if peaks corresponding search coniditions (min_peak_height, min_peak_distance) was not found, 
 *                              -1 will be written as output
 * @param[in] peaks_indices_num Number of highest peaks to find
 */
void neuton_dsp_findpeaks_i16(neuton_i16_t p_input[],
                              neuton_u16_t num,
                              neuton_i16_t min_peak_height,
                              neuton_u16_t min_peak_distance,
                              neuton_i16_t peaks_indices[],
                              neuton_u16_t peaks_indices_num);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SPECTRAL_FINDPEAKS_H_ */

/**
 * @}
 */
