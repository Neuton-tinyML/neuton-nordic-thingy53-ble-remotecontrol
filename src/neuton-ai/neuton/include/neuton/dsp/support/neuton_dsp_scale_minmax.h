/**
 *
 * @defgroup neuton_dsp_scale_minmax Min-Max Scaling
 * @{
 * @ingroup neuton_dsp_support
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_SUPPORT_SCALE_MINMAX_H_
#define _NEUTON_DSP_SUPPORT_SCALE_MINMAX_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Min-Max scaling of the floating-point vector ( y = (x - min) / (max - min) )
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples in input vector
 * @param[in]  min          Minimum scaling factor
 * @param[in]  max          Maximum scaling factor
 * @param[out] p_output     Pointer to the output scaled vector
 */
void neuton_dsp_scale_minmax_f32(const neuton_f32_t* p_input,
                                 neuton_u16_t        num,
                                 const neuton_f32_t  min,
                                 const neuton_f32_t  max,
                                 neuton_f32_t*       p_output);

/**
 * @brief Min-Max scaling of the INT8 vector ( y = (x - min) / (max - min) )
 * @note In order not to lose accuracy when dividing, the subtraction result (x - min) is multiplied by NEUTON_INT8_QFACTOR
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples in input vector
 * @param[in]  min          Minimum scaling factor
 * @param[in]  max          Maximum scaling factor
 * @param[out] p_output     Pointer to the output scaled vector
 */
void neuton_dsp_scale_minmax_i8(const neuton_i8_t* p_input,
                                neuton_u16_t       num,
                                const neuton_i8_t  min,
                                const neuton_i8_t  max,
                                neuton_i8_t*       p_output);

/**
 * @brief Min-Max scaling of the INT16 vector ( y = (x - min) / (max - min) )
 * @note In order not to lose accuracy when dividing, the subtraction result (x - min) is multiplied by NEUTON_INT16_QFACTOR
 * 
 * @param[in]  p_input      Pointer to the input vector
 * @param[in]  num          Number of samples in input vector
 * @param[in]  min          Minimum scaling factor
 * @param[in]  max          Maximum scaling factor
 * @param[out] p_output     Pointer to the output scaled vector
 */
void neuton_dsp_scale_minmax_i16(const neuton_i16_t* p_input,
                                 neuton_u16_t        num,
                                 const neuton_i16_t  min,
                                 const neuton_i16_t  max,
                                 neuton_i16_t*       p_output);

/** @def neuton_dsp_scale_minmax_int_q
 *
 * @brief Macro for Min-Max scaling of integer variable with quantization
 * 
 * @param[in] var      Variable for scaling
 * @param[in] qfactor  Quantization factor
 * @param[in] min      Minimum scaling factor
 * @param[in] max      Maximum scaling factor
 */
#define neuton_dsp_scale_minmax_int_q(var, qfactor, min, max) \
    (((neuton_i32_t)(var - min) * qfactor) / (max - min))

/** @def neuton_dsp_scale_minmax_float
 *
 * @brief Macro for Min-Max scaling of floating-point variable
 * 
 * @param[in] var    Variable for scaling
 * @param[in] min    Minimum scaling factor
 * @param[in] max    Maximum scaling factor
 */
#define neuton_dsp_scale_minmax_float(var, min, max) ((neuton_f32_t)(var - min) / (max - min))

/** @def neuton_dsp_scale_minmax_float_q
 *
 * @brief Macro for Min-Max scaling of floating-point variable with quantization
 * 
 * @param[in] var      Variable for scaling
 * @param[in] qfactor  Quantization factor
 * @param[in] min      Minimum scaling factor
 * @param[in] max      Maximum scaling factor
 */
#define neuton_dsp_scale_minmax_float_q(var, qfactor, min, max) \
    (((var - min) * qfactor) / (max - min))

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SUPPORT_SCALE_MINMAX_H_ */

/**
 * @}
 */
