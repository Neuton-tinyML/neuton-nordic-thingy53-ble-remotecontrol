/**
 *
 * @defgroup neuton_dsp_statistic_pk2pk Peak to Peak 
 * @{
 * @ingroup neuton_dsp_statistic
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_STAT_PEAK2PEAK_FUNCTIONS_H_
#define _NEUTON_DSP_STAT_PEAK2PEAK_FUNCTIONS_H_

#include <neuton/dsp/neuton_dsp_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a floating-point vector.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                size_t window_size, 
                                neuton_f32_t* p_pk2pk_lf, neuton_f32_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a floating-point vector, using values ​​in increments of 'stride'.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                size_t stride, size_t window_size, 
                                neuton_f32_t* p_pk2pk_lf, neuton_f32_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a INT8 fixed-point vector.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t window_size, 
                                neuton_i16_t* p_pk2pk_lf, neuton_i16_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a INT8 fixed-point vector, using values ​​in increments of 'stride'.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                size_t stride, size_t window_size, 
                                neuton_i16_t* p_pk2pk_lf, neuton_i16_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a INT16 fixed-point vector.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t window_size, 
                                neuton_i32_t* p_pk2pk_lf, neuton_i32_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a INT16 fixed-point vector, using values ​​in increments of 'stride'.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                size_t stride, size_t window_size, 
                                neuton_i32_t* p_pk2pk_lf, neuton_i32_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a INT32 fixed-point vector.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                size_t window_size, 
                                neuton_i32_t* p_pk2pk_lf, neuton_i32_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for Low and High frequency components of signal, 
 *          represented as a INT32 fixed-point vector, using values ​​in increments of 'stride'.
 * 
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * @param[out]  p_pk2pk_lf      Pointer to store Peak-to-Peak amplitude for Low frequency component
 * @param[out]  p_pk2pk_hf      Pointer to store Peak-to-Peak amplitude for High frequency component
 */
void neuton_dsp_pk2pk_lf_hf_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                size_t stride, size_t window_size, 
                                neuton_i32_t* p_pk2pk_lf, neuton_i32_t* p_pk2pk_hf);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a floating-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_f32_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_f32_t neuton_dsp_pk2pk_hf_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a floating-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_f32_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_f32_t neuton_dsp_pk2pk_hf_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a INT8 fixed-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i16_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_i16_t neuton_dsp_pk2pk_hf_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a INT8 fixed-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i16_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_i16_t neuton_dsp_pk2pk_hf_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a INT16 fixed-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_hf_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a INT16 fixed-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_hf_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a INT32 fixed-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_hf_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for High frequency component of signal, 
 *          represented as a INT32 fixed-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for High frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_hf_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a floating-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_f32_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_f32_t neuton_dsp_pk2pk_lf_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a floating-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_f32_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_f32_t neuton_dsp_pk2pk_lf_f32_s(const neuton_f32_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a INT8 fixed-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i16_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_i16_t neuton_dsp_pk2pk_lf_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a INT8 fixed-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i16_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_i16_t neuton_dsp_pk2pk_lf_i8_s(const neuton_i8_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a INT16 fixed-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_lf_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a INT16 fixed-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_lf_i16_s(const neuton_i16_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a INT32 fixed-point vector.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples in input vector
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_lf_i32(const neuton_i32_t* p_input, neuton_u16_t num,
                                     size_t window_size);

/**
 * @brief Finds Peak-to-Peak amplitude for Low frequency component of signal, 
 *          represented as a INT32 fixed-point vector, using values ​​in increments of 'stride'.
 *
 * @param[in]   p_input         Pointer to the input vector
 * @param[in]   num             Number of samples with 'stride' in input vector
 * @param[in]   stride          Vector element offset stride
 * @param[in]   window_size     Determines window size for calculation moving average filter sum,
 *                              window_size affect attenuation for frequencies
 * 
 * @return  neuton_i32_t  Peak-to-Peak amplitude for Low frequency component 
 */
neuton_i32_t neuton_dsp_pk2pk_lf_i32_s(const neuton_i32_t* p_input, neuton_u16_t num,
                                     size_t stride, size_t window_size);

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_STAT_PEAK2PEAK_FUNCTIONS_H_ */

/**
 * @}
 */
