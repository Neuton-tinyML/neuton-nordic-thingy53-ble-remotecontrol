/**
 *
 * @defgroup neuton_debug Debug Utils
 * @{
 *
 * @brief
 *
 */

#ifndef _NEUTON_DEBUG_H_
#define _NEUTON_DEBUG_H_

/**
 * @brief Macro for verifying that the provided condition is true. It will cause the exterior
 *        function to return an error value if it is not.
 *
 * @param[in] is_true     Boolean condition to check.
 * @param[in] ret_val     The value to be returned if the checks fails
 */
#define NEUTON_RETURN_IF(is_true, ret_val) \
    do                                     \
    {                                      \
        if ((is_true)) { return ret_val; } \
    }                                      \
    while (0)

/**
 * @brief Macro for return values ​​to indicate potential divide-by-zero in the DSP functions
 * 
 */
#ifndef NEUTON_DSP_ZERO_DIV_FLAG
#define NEUTON_DSP_ZERO_DIV_FLAG 0
#endif

#ifdef NEUTON_DSP_ENABLE_RUNTIME_CHECKS
#define NEUTON_DSP_RETURN_IF(is_true, ret_val) NEUTON_RETURN_IF(is_true, ret_val)
#else
#define NEUTON_DSP_RETURN_IF(...) ;
#endif  // NEUTON_DSP_ENABLE_RUNTIME_CHECKS

#define NEUTON_LOG_ENABLE 0

#if NEUTON_LOG_ENABLE == 1
#include <stdio.h>
#define NEUTON_LOG(...)         printf(__VA_ARGS__)
#else
#define NEUTON_LOG(...)
#endif // NEUTON_LOG_ENABLE

#define NEUTON_ASSERT_ENABLE 0

#if NEUTON_ASSERT_ENABLE == 1
#include <assert.h>
#define neuton_assert(x) assert(x)
#else
#define neuton_assert(x) ;
#endif // NEUTON_ASSERT_ENABLE

#endif /* _NEUTON_DEBUG_H_ */

/**
 * @}
 */
