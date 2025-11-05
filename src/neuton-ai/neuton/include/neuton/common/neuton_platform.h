#ifndef _NEUTON_PLATFORM_H_
#define _NEUTON_PLATFORM_H_

#include "neuton_debug.h"

#define __NEUTON_STATIC_INLINE static inline

#if defined(__GNUC__)
#define __NEUTON_WEAK               __attribute__((weak))
#define __NEUTON_ALIGN(x)           __attribute__((aligned(x)))
#define __NEUTON_ALIGNED            __attribute__((aligned))
#define __NEUTON_PACKED             __attribute__((__packed__))
#define __NEUTON_STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#elif defined(__ICCARM__)
#define __NEUTON_WEAK               __weak
#define __NEUTON_PACKED             __packed
#define __NEUTON_ALIGNED            __attribute__((aligned))
#define __NEUTON_ALIGN(x)           __attribute__((aligned(x)))
#define __NEUTON_STATIC_FORCEINLINE _Pragma("inline=forced") __NEUTON_STATIC_INLINE
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#define __NEUTON_WEAK               __attribute__((weak))
#define __NEUTON_ALIGN(x)           __attribute__((aligned(x)))
#define __NEUTON_ALIGNED            __attribute__((aligned))
#define __NEUTON_PACKED             __attribute__((packed))
#define __NEUTON_STATIC_FORCEINLINE __NEUTON_STATIC_INLINE
#else
#define __NEUTON_WEAK               __attribute__((weak))
#define __NEUTON_ALIGN(x)           __attribute__((aligned(x)))
#define __NEUTON_ALIGNED            __attribute__((aligned))
#define __NEUTON_PACKED             __attribute__((__packed__))
#define __NEUTON_STATIC_FORCEINLINE __NEUTON_STATIC_INLINE
#endif

#define NEUTON_INT8_MAX           ((neuton_i8_t)(0x7F))
#define NEUTON_INT8_MIN           ((neuton_i8_t)(0x80))
#define NEUTON_INT8_ABSMAX        ((neuton_i8_t)(0x7F))
#define NEUTON_INT8_ABSMIN        ((neuton_i8_t)0)
#define NEUTON_INT8_QFACTOR       (127)
#define NEUTON_INT8_SIGN_BIT      ((neuton_i8_t)1 << 7)
#define NEUTON_INT8_CHECK_SIGN(x) (bool)((x) & NEUTON_INT8_SIGN_BIT)

#define NEUTON_INT16_MAX           ((neuton_i16_t)(0x7FFF))
#define NEUTON_INT16_MIN           ((neuton_i16_t)(0x8000))
#define NEUTON_INT16_ABSMAX        ((neuton_i16_t)(0x7FFF))
#define NEUTON_INT16_ABSMIN        ((neuton_i16_t)0)
#define NEUTON_INT16_QFACTOR       ((neuton_i16_t)32767)
#define NEUTON_INT16_SIGN_BIT      ((neuton_i16_t)1 << 15)
#define NEUTON_INT16_CHECK_SIGN(x) (bool)((x) & NEUTON_INT16_SIGN_BIT)

#define NEUTON_UINT16_MAX ((neuton_u16_t)(0xFFFF))
#define NEUTON_UINT16_MIN ((neuton_u16_t)(0x0000))

#define NEUTON_INT32_MAX           ((neuton_i32_t)(0x7FFFFFFFL))
#define NEUTON_INT32_MIN           ((neuton_i32_t)(0x80000000L))
#define NEUTON_INT32_ABSMAX        ((neuton_i32_t)(0x7FFFFFFFL))
#define NEUTON_INT32_ABSMIN        ((neuton_i32_t)0)
#define NEUTON_INT32_QFACTOR       ((neuton_i32_t)2147483648)
#define NEUTON_INT32_SIGN_BIT      ((neuton_i32_t)1 << 31)
#define NEUTON_INT32_CHECK_SIGN(x) (bool)((x) & NEUTON_INT32_SIGN_BIT)

// smallest such that 1.0+NEUTON_F32_EPSILON != 1.0
#define NEUTON_F32_EPSILON       ((neuton_f32_t)1.192092896e-07F)
#define NEUTON_F32_MAX           ((neuton_f32_t)3.402823466e+38F)
#define NEUTON_F32_MIN           -NEUTON_F32_MAX
#define NEUTON_F32_NP_MIN        ((neuton_f32_t)1.175494351e-38F)  // min normalized positive value
#define NEUTON_F32_CHECK_SIGN(x) (bool)(signbit(x))

#define NEUTON_UNUSED(x) ((void)(x))

#define NEUTON_VOID_VALUE

#define __NEURON_Q8_BIT  (8)
#define __NEURON_Q16_BIT (16)
#define __NEURON_Q32_BIT (32)

#define __NEURON_BIAS_Q8  (((neuton_u16_t)1 << __NEURON_Q8_BIT) - 1)
#define __NEURON_BIAS_Q16 (((neuton_u32_t)1 << __NEURON_Q16_BIT) - 1)
#define __NEURON_BIAS_Q32 ((neuton_f32_t)1.0f)

#endif /* _NEUTON_PLATFORM_H_ */