/**
 *
 * @defgroup neuton_dsp_transform_fft_f32   Floating-point 32-bit FFT
 * @{
 * @ingroup neuton_dsp_transform_fft
 *
 * @brief
 *
 */
#ifndef _NEUTON_DSP_TRANSFORM_FFT_F32_H_
#define _NEUTON_DSP_TRANSFORM_FFT_F32_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct neuton_dsp_cfft_f32_s
{
    neuton_u16_t        len;              /**< length of the FFT. */
    neuton_u16_t        bitrev_table_len; /**< bit reversal table length. */
    const neuton_u16_t* p_bitrev_table;   /**< points to the bit reversal table. */
    const neuton_f32_t* p_twiddle;        /**< points to the Twiddle factor table. */
} neuton_dsp_cfft_f32_t;

typedef struct neuton_dsp_rfft_f32_s
{
    neuton_dsp_cfft_f32_t cfft;           /**< Internal CFFT structure. */
    neuton_u16_t          len;            /**< length of the real sequence */
    const neuton_f32_t*   p_twiddle_rfft; /**< Twiddle factors real stage  */
} neuton_dsp_rfft_f32_t;

/**
 * @brief Complex FFT radix function type
 *
 */
typedef void (*neuton_dsp_cfft_radix_func_f32_t)(const neuton_dsp_cfft_f32_t* p_cfft,
                                                 neuton_f32_t*                p_input);

/**
 * @brief Initialize real FFT instance structure
 *
 * @param[in, out]  p_rfft              Pointer to instance of real FFT structure to initialize @ref neuton_dsp_rfft_f32_t
 * @param[in]       len                 Length of the real FFT
 * @param[in]       p_twiddle_rfft      Pointer to the Real Twiddle factor table, can be generated with @ref neuton_dsp_rfft_twiddle_factors_f32
 * @param[in]       p_twiddle_cfft      Pointer to the Twiddle factor table, can be generated with @ref neuton_dsp_cfft_twiddle_factors_f32
 * @param[in]       p_bitrev_table      Pointer to the Bit reverse index table
 * @param[in]       bitrev_table_len    Bit reverse index table length
 */
void neuton_dsp_rfft_init_f32(neuton_dsp_rfft_f32_t* p_rfft,
                              neuton_u16_t           len,
                              const neuton_f32_t*    p_twiddle_rfft,
                              const neuton_f32_t*    p_twiddle_cfft,
                              const neuton_u16_t*    p_bitrev_table,
                              neuton_u16_t           bitrev_table_len);

/**
 * @brief   The floating-point real FFT function.
 *          Real FFT algorithms take advantage of the symmetry properties of the FFT and have a
 *          speed advantage over complex algorithms of the same length.
 *          This function can compute results "in-place" of input buffer
 *
 * @param[in]   p_rfft      Pointer to instance of real FFT structure @ref neuton_dsp_rfft_f32_t
 * @param[in]   p_input     Pointer to buffer with input samples, the complex FFT computes in-place  and will modify input buffer with FFT results.
 * @param[out]  p_output    Pointer to the output buffer, can be the same as p_input.
 *                          The results will be written to output array in the interleaved fashion:
 *                          <pre>{real[0], imag[0], real[1], imag[1], ...} </pre>
 */
void neuton_dsp_rfft_f32(neuton_dsp_rfft_f32_t* p_rfft,
                         neuton_f32_t*          p_input,
                         neuton_f32_t*          p_output);

/**
 * @brief   The floating-point real FFT function with custom radix function to use.
 *          Real FFT algorithms take advantage of the symmetry properties of the FFT and have a
 *          speed advantage over complex algorithms of the same length.
 *          This function can compute results "in-place" of input buffer
 *
 * @param[in]   p_rfft      Pointer to instance of real FFT structure @ref neuton_dsp_rfft_f32_t
 * @param[in]   p_input     Pointer to buffer with input samples, the complex FFT computes in-place and will modify input buffer with FFT results.
 * @param[out]  p_output    Pointer to the output buffer, can be the same as p_input.
 *                          The results will be written to output array in the interleaved fashion:
 *                          <pre>{real[0], imag[0], real[1], imag[1], ...} </pre>
 * @param[in]   radix_func  Custom FFT Radix function to compute complex FFT, refer to
 *                          neuton_dsp_cfft_radix8by2_f32, neuton_dsp_cfft_radix8by4_f32 or neuton_dsp_cfft_radix8_f32
 */
void neuton_dsp_rfft_rdx_f32(const neuton_dsp_rfft_f32_t*     p_rfft,
                             neuton_f32_t*                    p_input,
                             neuton_f32_t*                    p_output,
                             neuton_dsp_cfft_radix_func_f32_t radix_func);

/**
 * @brief Initialize complex FFT instance structure
 *
 * @param[in, out]  p_cfft              Pointer to instance of complex FFT structure to initialize @ref neuton_dsp_cfft_f32_t
 * @param[in]       len                 Length of the FFT, should be power of 2, e.g.32,64,128,256,512,1024,etc
 * @param[in]       p_twiddle_cfft      Pointer to the Twiddle factor table, can be generated with @ref neuton_dsp_cfft_twiddle_factors_f32
 * @param[in]       p_bitrev_table      Pointer to the Bit reverse index table
 * @param[in]       bitrev_table_len    Bit reverse index table length
 */
void neuton_dsp_cfft_init_f32(neuton_dsp_cfft_f32_t* p_cfft,
                              neuton_u16_t           len,
                              const neuton_f32_t*    p_twiddle_cfft,
                              const neuton_u16_t*    p_bitrev_table,
                              neuton_u16_t           bitrev_table_len);

/**
 * @brief The floating-point complex FFT function
 *
 * @param[in]       p_cfft      Pointer to instance of complex FFT structure @ref neuton_dsp_cfft_f32_t
 * @param[in, out]  p_input     Pointer to buffer with input samples, the FFT computes in-place and
 *                              will modify input buffer with FFT results. The results will be written to input array in the
 *                              interleaved fashion: <pre>{real[0], imag[0], real[1], imag[1], ...} </pre>
 *
 * @param[in]       bitreverse_flag     Flag that enables (bitreverse_flagR=1) or disables(bitreverse_flagR=0) bit reversal of output
 */
void neuton_dsp_cfft_f32(const neuton_dsp_cfft_f32_t* p_cfft,
                         neuton_f32_t*                p_input,
                         neuton_u8_t                  bitreverse_flag);

/**
 * @brief The floating-point complex FFT function with custom radix function to use
 *
 * @param[in]       p_cfft      Pointer to instance of complex FFT structure @ref neuton_dsp_cfft_f32_t
 * @param[in, out]  p_input     Pointer to buffer with input samples, the FFT computes in-place and
 *                              will modify input buffer with FFT results. The results will be written to input array in the
 *                              interleaved fashion: <pre>{real[0], imag[0], real[1], imag[1], ...} </pre>
 *
 * @param[in]       bitreverse_flag     Flag that enables (bitreverse_flagR=1) or disables (bitreverse_flagR=0) bit reversal of output
 * @param[in]       radix_func          Custom FFT Radix function to compute FFT, refer to
 *                                      neuton_dsp_cfft_radix8by2_f32, neuton_dsp_cfft_radix8by4_f32 or neuton_dsp_cfft_radix8_f32
 */
void neuton_dsp_cfft_rdx_f32(const neuton_dsp_cfft_f32_t*     p_cfft,
                             neuton_f32_t*                    p_input,
                             neuton_u8_t                      bitreverse_flag,
                             neuton_dsp_cfft_radix_func_f32_t radix_func);

/**
 * @brief   The floating-point complex FFT uses a mixed-radix algorithm.
 *          Multiple radix-2 stages are performed along with a radix-1 stage, as needed.
 *          The algorithm supports lengths of [16, 128, 1024] and each length uses a different
 *          twiddle factor table.
 *
 * @param[in]       p_cfft      Pointer to instance of complex FFT structure @ref neuton_dsp_cfft_f32_t
 * @param[in, out]  p_input     Pointer to buffer with input samples, the FFT computes in-place and
 *                              will modify input buffer with FFT results. The results will be written to input array in the
 *                              interleaved fashion: <pre>{real[0], imag[0], real[1], imag[1], ...} </pre>
 */
void neuton_dsp_cfft_radix8by2_f32(const neuton_dsp_cfft_f32_t* p_cfft, neuton_f32_t* p_input);

/**
 * @brief   The floating-point complex FFT uses a mixed-radix algorithm.
 *          Multiple radix-4 stages are performed along with a radix-1 stage, as needed.
 *          The algorithm supports lengths of [32, 256, 2048] and each length uses a different
 *          twiddle factor table.
 *
 * @param[in]       p_cfft      Pointer to instance of complex FFT structure @ref neuton_dsp_cfft_f32_t
 * @param[in, out]  p_input     Pointer to buffer with input samples, the FFT doing in place and
 *                              will modify input buffer with FFT results. The results will be written to input array in the
 *                              interleaved fashion: <pre>{real[0], imag[0], real[1], imag[1], ...} </pre>
 */
void neuton_dsp_cfft_radix8by4_f32(const neuton_dsp_cfft_f32_t* p_cfft, neuton_f32_t* p_input);

/**
 * @brief   The floating-point complex FFT uses a radix algorithm.
 *          Single radix-8  1-stage, algorithm.
 *          The algorithm supports lengths of [64, 512, 4096] and each length uses a different
 *          twiddle factor table.
 *
 * @param[in]       p_cfft      Pointer to instance of complex FFT structure @ref neuton_dsp_cfft_f32_t
 * @param[in, out]  p_input     Pointer to buffer with input samples, the FFT doing in place and
 *                              will modify input buffer with FFT results. The results will be
 *                              written to input array in the interleaved fashion: <pre>{real[0], imag[0], real[1], imag[1], ...} </pre>
 */
void neuton_dsp_cfft_radix8_f32(const neuton_dsp_cfft_f32_t* p_cfft, neuton_f32_t* p_input);

/**
 * @brief Generate floating-point complex twiddle factors buffer
 *
 * @param[out] p_twiddle_cfft       Output complex twiddle factors buffer, the output buffer should be 2*fft_len in length
 *                                  the twiddle factors will be written in interleaved fashion (cos0,sin0,cos1,sin1,..., cosN,sinN), 
 * @param[in]  fft_len              FFT length for which complex twiddle factors table will be
 *                                  generated, should be in power of 2
 * 
 * @return Number of twiddle factors in the output buffer, if fft_len is not power of 2, returns 0
 */
neuton_u16_t neuton_dsp_cfft_twiddle_factors_f32(neuton_f32_t* p_twiddle_cfft,
                                                 neuton_u16_t  fft_len);

/**
 * @brief Generate floating-point real twiddle factors buffer
 *
 * @param[out] p_twiddle_rfft       Output real twiddle factors buffer, the output buffer should be fft_len in length
 *                                  the twiddle factors will be written in interleaved fashion (cos0,sin0,cos1,sin1,..., cosN,sinN), 
 * @param[in]  fft_len              FFT length for which twiddle factors table will be  generated, should be in power of 2
 * 
 *  @return Number of twiddle factors in the output buffer, if fft_len is not power of 2, returns 0
 */
neuton_u16_t neuton_dsp_rfft_twiddle_factors_f32(neuton_f32_t* p_twiddle_rfft,
                                                 neuton_u16_t  fft_len);

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_TRANSFORM_FFT_F32_H_ */

/**
 * @}
 */
