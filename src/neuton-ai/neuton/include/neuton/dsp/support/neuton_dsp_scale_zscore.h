/**
 *
 * @defgroup neuton_dsp_scaling_zscore Z-score Scaling
 * @{
 * @ingroup neuton_dsp_support
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SUPPORT_SCALE_ZSCORE_H_
#define _NEUTON_DSP_SUPPORT_SCALE_ZSCORE_H_

#include <neuton/neuton_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Z-score scaling of the floating-point vector ( y = (x - mean) / stddev )
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples in input vector
 * @param[in]  mean         Mean scaling factor
 * @param[in]  stddev       Standard deviation scaling factor
 * @param[out] p_output     Pointer to the output scaled vector
 */
void neuton_dsp_scale_zscore_f32(const neuton_f32_t* p_input, neuton_u16_t num,
                                    const neuton_f32_t mean, const neuton_f32_t stddev,
                                    neuton_f32_t* p_output);

/**
 * @brief Z-score scaling of the INT8 vector ( y = (x - mean) / stddev )
 * @note In order not to lose accuracy when dividing, the subtraction result (x - mean) is multiplied by NEUTON_INT8_QFACTOR
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples in input vector
 * @param[in]  mean         Mean scaling factor
 * @param[in]  stddev       Standard deviation scaling factor
 * @param[out] p_output     Pointer to the output scaled vector
 */
void neuton_dsp_scale_zscore_i8(const neuton_i8_t* p_input, neuton_u16_t num,
                                const neuton_i8_t mean, const neuton_i8_t stddev,
                                neuton_i8_t* p_output);

/**
 * @brief Z-score scaling of the INT16 vector ( y = (x - mean) / stddev )
 * @note In order not to lose accuracy when dividing, the subtraction result (x - mean) is multiplied by NEUTON_INT16_QFACTOR
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples in input vector
 * @param[in]  mean         Mean scaling factor
 * @param[in]  stddev       Standard deviation scaling factor
 * @param[out] p_output     Pointer to the output scaled vector
 */
void neuton_dsp_scale_zscore_i16(const neuton_i16_t* p_input, neuton_u16_t num,
                                const neuton_i16_t mean, const neuton_i16_t stddev,
                                neuton_i16_t* p_output);

/** @def neuton_dsp_scale_zscore_ivar
 *
 * @brief Macro for Z-score scaling of integer variable with quantization
 * 
 * @param[in, out] var      Variable for scaling
 * @param[in]      qfactor  Quantization factor
 * @param[in]      mean     Mean scaling factor
 * @param[in]      stddev   Standard deviation scaling factor
 */
#define neuton_dsp_scale_zscore_ivar(var, qfactor, mean, stddev) \
        (((neuton_i32_t)(var - mean) * qfactor) / stddev)

/** @def neuton_dsp_scale_zscore_fvar
 *
 * @brief Macro for Z-score scaling of floating-point variable
 * 
 * @param[in, out] var    Variable for scaling
 * @param[in]      mean   Mean scaling factor
 * @param[in]      stddev Standard deviation scaling factor
 */
#define neuton_dsp_scale_zscore_fvar(var, mean, stddev)   \
        ((var - mean) / stddev)

/** @def neuton_dsp_scale_zscore_qfvar
 *
 * @brief Macro for Z-score scaling of floating-point variable with quantization
 * 
 * @param[in, out] var      Variable for scaling
 * @param[in]      qfactor  Quantization factor
 * @param[in]      mean     Mean scaling factor
 * @param[in]      stddev   Standard deviation scaling factor
 */
#define neuton_dsp_scale_zscore_qfvar(var, qfactor, mean, stddev)   \
        (((var - mean) * qfactor) / stddev)

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SUPPORT_SCALE_ZSCORE_H_ */

/**
 * @}
 */
