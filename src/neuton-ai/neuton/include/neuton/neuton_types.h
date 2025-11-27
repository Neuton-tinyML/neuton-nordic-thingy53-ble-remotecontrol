#ifndef _NEUTON_TYPES_H_
#define _NEUTON_TYPES_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 8-bit signed integer type definition.
 */
typedef int8_t neuton_i8_t;

/**
 * @brief 8-bit unsigned integer type definition.
 */
typedef uint8_t neuton_u8_t;

/**
 * @brief 16-bit signed integer type definition.
 */
typedef int16_t neuton_i16_t;

/**
 * @brief 16-bit unsigned integer type definition.
 */
typedef uint16_t neuton_u16_t;

/**
  * @brief 32-bit signed integer type definition.
  */
typedef int32_t neuton_i32_t;

/**
 * @brief 32-bit unsigned integer type definition.
 */
typedef uint32_t neuton_u32_t;

/**
 * @brief 64-bit signed integer type definition.
 */
typedef int64_t neuton_i64_t;

/**
 * @brief 64-bit unsigned integer type definition.
 */
typedef uint64_t neuton_u64_t;

/**
 * @brief 32-bit floating-point type definition.
 */
typedef float neuton_f32_t;

/**
 * @brief 64-bit floating-point type definition.
 */
typedef double neuton_f64_t;

/**
 * @brief Architecture size_t type definition.
 */
typedef size_t neuton_sz_t;

/**
 * @brief Generic Neuton operation status code
 */
typedef enum neuton_status_e
{
    NEUTON_STATUS_INPROGRESS = 126,

    /** Operation successful */
    NEUTON_STATUS_SUCCESS = 0,

    /** The operation failed with an unspecified error */
    NEUTON_STATUS_UNSPECIFIED_ERROR = -1,

    /** The argument supplied to the operation was invalid */
    NEUTON_STATUS_INVALID_ARGUMENT = -2,

    /** The argument supplied to the operation was NULL */
    NEUTON_STATUS_NULL_ARGUMENT = -3,

    /** The requested operation was not available */
    NEUTON_STATUS_UNAVAILABLE = -4,

    /** The operation or service not supported */
    NEUTON_STATUS_NOT_SUPPORTED = -5,

    /** Wrong memory alignment */
    NEUTON_STATUS_WRONG_MEM_ALIGNMENT = -6,
} neuton_status_t;

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_TYPES_H_ */