/**
 *
 * @defgroup neuton_dsp_f24 Float 24
 * @{
 * @ingroup neuton_dsp_support
 *
 * @brief Custom numeric library for integer calculation with high correlation to float
 *
 */
#ifndef _NEUTON_DSP_SUPPORT_FLOAT24_H_
#define _NEUTON_DSP_SUPPORT_FLOAT24_H_

#include <neuton/neuton_types.h>
#include <neuton/common/neuton_platform.h>

#ifdef   __cplusplus
extern "C"
{
#endif

#define NEUTON_F24_SIGNED           0x40
#define NEUTON_F24_UNSIGNED         0
#define NEUTON_F24_SIGN(x)         ((neuton_u8_t)(x.exps & NEUTON_F24_SIGNED))

// ///////////////////////////////////////////////////////////////////////////
/** Short name macro */
#define f24_init                    neuton_f24_init
#define i16_to_f24                  neuton_i16_to_f24
#define i8_to_f24                   neuton_i8_to_f24
#define f24_to_i32                  neuton_f24_to_i32
#define f24_mul                     neuton_f24_mul
#define f24_add                     neuton_f24_add
#define f24_addx                    neuton_f24_addx
#define f24_div                     neuton_f24_div
#define f24_sqrt                    neuton_f24_sqrt
#define f24_get_exp                 neuton_f24_get_exp

// ///////////////////////////////////////////////////////////////////////////

/**
 * @brief Container for Float24 representation
 * 
 */
typedef struct neuton_f24_s
{
    /** Mantissa*/
    neuton_u16_t man;

    /** Exponenta with sign */
    neuton_u8_t exps;
} neuton_f24_t;

/**
 * @brief Convert INT16 to Float24
 */
neuton_f24_t neuton_i16_to_f24(neuton_i16_t x);

/**
 * @brief Convert INT8 to Float24
 */
neuton_f24_t neuton_i8_to_f24(neuton_i8_t x);

/**
 * @brief Convert Float24 to INT32 value
 * 
 * @param[in] x                 Float24 value to convert
 * @param[in] required_exp      Required exponent bit shift, affect fractional part accuracy
 * 
 * @return neuton_i32_t Converted INT32 value
 */
neuton_i32_t neuton_f24_to_i32(neuton_f24_t x, neuton_i8_t required_exp);

/**
 * @brief Float24 multiplication (x * y) -> z
 */
neuton_f24_t neuton_f24_mul(neuton_f24_t x, neuton_f24_t y);

/**
 * @brief Float24 addition (x + y) -> z
 */
neuton_f24_t neuton_f24_add(neuton_f24_t x, neuton_f24_t y);

/**
 * @brief Float24 division (x / y) -> z
 */
neuton_f24_t neuton_f24_div(neuton_f24_t x, neuton_f24_t y);

/**
 * @brief Float24 square root (sqrt(x)) -> z
 */
neuton_f24_t neuton_f24_sqrt(neuton_f24_t x);

/**
 * @brief Initialize Float24 value from metainformaton
 * 
 * @param[in] mantissa      Mantissa
 * @param[in] exp           Exponent
 * @param[in] sign          Sign byte: NEUTON_F24_SIGNED or NEUTON_F24_UNSIGNED
 * 
 * @return neuton_f24_t Float24 value
 */
neuton_f24_t neuton_f24_init(neuton_u16_t mantissa, neuton_i8_t exp, 
                              neuton_u8_t sign);

/**
 * @brief Extended Float24 addition function (x + y) -> z
 * @warning To perform addition, the mantissa and exponents of X and Y must be bit aligned
 * 
 * @param[in] x_man         Mantissa of first argument X
 * @param[in] x_exp         Exponent of first argument X
 * @param[in] x_sign        Sign byte of first argument X
 * @param[in] y_man         Mantissa of second argument Y
 * @param[in] y_exp         Exponent of second argument Y
 * @param[in] y_sign        Sign byte of second argument Y
 * 
 * @return neuton_f24_t Float24 result of addition
 */
neuton_f24_t neuton_f24_addx(neuton_u16_t x_man, neuton_i8_t x_exp, neuton_u8_t x_sign,
                            neuton_u16_t y_man, neuton_i8_t y_exp, neuton_u8_t y_sign);

/**
 * @brief Get a pointer to an internal utility array [0-255] to help figure out
 *        how many bits is occupied in byte
 */
const neuton_u8_t* neuton_f24_get_highbit_helper(void);

/**
 * @brief Get exponent of Float24 value
 */
__NEUTON_STATIC_FORCEINLINE 
neuton_i8_t neuton_f24_get_exp(neuton_f24_t x)
{
    return (neuton_i8_t)((x.exps & 0x80) ? -(x.exps & 0x3F) : (x.exps & 0x3F));
}


#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_DSP_SUPPORT_FLOAT24_H_ */

/**
 * @}
 */
