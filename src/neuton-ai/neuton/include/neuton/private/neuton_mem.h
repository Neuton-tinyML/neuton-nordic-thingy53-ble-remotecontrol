#ifndef _NEUTON_MEMORY_OPERATIONS_H_
#define _NEUTON_MEMORY_OPERATIONS_H_

#include "neuton_common.h"

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * @brief Read 4 INT8 values as INT32 value, from INT8 vector
 *
 * @param[in] p_input   Pointer to the input vector
 *
 * @return  neuton_i32_t  4x INT8 values
 */
__NEUTON_STATIC_FORCEINLINE neuton_i32_t read_i8x4(neuton_i8_t const* p_input)
{
    neuton_i32_t val =  ((neuton_i32_t)(p_input[3] & 0x0FF) << 24) | 
                        ((neuton_i32_t)(p_input[2] & 0x0FF) << 16) | 
                        ((neuton_i32_t)(p_input[1] & 0x0FF) << 8)  | 
                        ( p_input[0] & 0x0FF);
    return val;
}


/**
 * @brief Read 2 INT16 values as INT32 value, from INT16 vector
 *
 * @param[in] p_input   Pointer to the input vector
 *
 * @return  neuton_i32_t  2x INT16 values
 */
__NEUTON_STATIC_FORCEINLINE neuton_i32_t read_i16x2(neuton_i16_t const* p_input)
{
    neuton_i32_t val = ((neuton_i32_t)p_input[1] << 16) | (p_input[0] & 0x0FFFF);

    return val;
}

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_MEMORY_OPERATIONS_H_ */