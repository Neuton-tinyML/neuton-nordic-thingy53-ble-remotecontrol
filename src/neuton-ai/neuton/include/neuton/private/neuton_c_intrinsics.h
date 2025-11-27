#ifndef _NEUTON_DSP_C_INTRINSICS_H_
#define _NEUTON_DSP_C_INTRINSICS_H_

#include <neuton/neuton_types.h>

#include "neuton_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define __NEUTON_CLZ  __CLZ
#define __NEUTON_SSAT __SSAT
#define __NEUTON_USAT __USAT
#define __NEUTON_ROR  __ROR

/**
  * @brief   Count leading zeros
  * @param [in]  value  Value to count the leading zeros
  * @return             number of leading zeros in value
  */
__NEUTON_STATIC_FORCEINLINE neuton_u8_t __CLZ(neuton_u32_t data)
{
    if (data == 0U) { return 32U; }

    neuton_u32_t count = 0U;
    neuton_u32_t mask  = 0x80000000U;

    while ((data & mask) == 0U)
    {
        count += 1U;
        mask = mask >> 1U;
    }
    return count;
}

/**
  * @brief   Signed Saturate
  * @details Saturates a signed value.
  * @param [in]  value  Value to be saturated
  * @param [in]    sat  Bit position to saturate to (1..32)
  * @return             Saturated value
  */
__NEUTON_STATIC_FORCEINLINE neuton_i32_t __SSAT(neuton_i32_t val, neuton_u32_t sat)
{
    if ((sat >= 1U) && (sat <= 32U))
    {
        const neuton_i32_t max = (neuton_i32_t)((1U << (sat - 1U)) - 1U);
        const neuton_i32_t min = -1 - max;
        if (val > max)
            return max;
        else if (val < min)
            return min;
    }
    return val;
}

/**
 * @brief Signed Saturate for integer 16-bit
 */
#define __SSAT16(x) CLIP_MINMAX((x), NEUTON_INT16_MIN, NEUTON_INT16_MAX)

/**
  * @brief   Unsigned Saturate
  * @details Saturates an unsigned value.
  * @param [in]  value  Value to be saturated
  * @param [in]  sat  Bit position to saturate to (0..31)
  * @return             Saturated value
  */
__NEUTON_STATIC_FORCEINLINE neuton_u32_t __USAT(neuton_i32_t val, neuton_u32_t sat)
{
    if (sat <= 31U)
    {
        const neuton_u32_t max = ((1U << sat) - 1U);
        if (val > (neuton_i32_t)max)
            return max;
        else if (val < 0)
            return 0U;
    }
    return (neuton_u32_t)val;
}

/**
 * @brief   Rotate Right in unsigned value (32 bit)
 * @details Rotate Right (immediate) provides the value of the contents of a register rotated by a variable number of bits.
 * @param [in]    op1  Value to rotate
 * @param [in]    op2  Number of Bits to rotate
 * @return               Rotated value
 */
__NEUTON_STATIC_FORCEINLINE neuton_u32_t __ROR(neuton_u32_t op1, neuton_u32_t op2)
{
    op2 %= 32U;
    return (op2 == 0U) ? op1 : ((op1 >> op2) | (op1 << (32U - op2)));
}

/**
  * @brief Clips INT64 to INT32 values.
  */
__NEUTON_STATIC_FORCEINLINE neuton_i32_t clip_i64_to_i32(neuton_i64_t x)
{
    return ((neuton_i32_t)(x >> 32) != ((neuton_i32_t)x >> 31)) ?
               ((0x7FFFFFFF ^ ((neuton_i32_t)(x >> 63)))) :
               (neuton_i32_t)x;
}

/**
 * @brief Clips INT64 to INT16 values.
 */
__NEUTON_STATIC_FORCEINLINE neuton_i16_t clip_i64_to_i16(neuton_i64_t x)
{
    return ((neuton_i32_t)(x >> 32) != ((neuton_i32_t)x >> 31)) ?
               ((0x7FFF ^ ((neuton_i16_t)(x >> 63)))) :
               (neuton_i16_t)(x >> 15);
}

/**
 * @brief Clips INT32 to INT8 values.
 */
__NEUTON_STATIC_FORCEINLINE neuton_i8_t clip_i32_to_i8(neuton_i32_t x)
{
    return ((neuton_i32_t)(x >> 24) != ((neuton_i32_t)x >> 23)) ?
               ((0x7F ^ ((neuton_i8_t)(x >> 31)))) :
               (neuton_i8_t)x;
}

/**
 * @brief Clips INT32 to INT16 values.
 */
__NEUTON_STATIC_FORCEINLINE neuton_i16_t clip_i32_to_i16(neuton_i32_t x)
{
    return ((neuton_i32_t)(x >> 16) != ((neuton_i32_t)x >> 15)) ?
               ((0x7FFF ^ ((neuton_i16_t)(x >> 31)))) :
               (neuton_i16_t)x;
}

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_DSP_C_INTRINSICS_H_ */
