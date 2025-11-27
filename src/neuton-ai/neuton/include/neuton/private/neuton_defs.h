#ifndef _NEUTON_DEFINITIONS_H_
#define _NEUTON_DEFINITIONS_H_

#include <neuton/common/neuton_platform.h>

#define NEUTON_USE_LOOPUNROLL    (0)
#define NEUTON_USE_MATH_ROUNDING (0)

#define NEUTON_FLOAT_TO_INT_FACTOR      (100U)
#define NEUTON_PERCENTAGE_TO_INT_FACTOR (1000U)

#define CONCAT2x(a, b) a##_##b
#define CONCAT2(a, b)  CONCAT2x(a, b)

#define CONCAT3x(a, b, c) a##_##b##_##c
#define CONCAT3(a, b, c)  CONCAT3x(a, b, c)

#define CONCAT4x(a, b, c, d) a##_##b##_##c##_##d
#define CONCAT4(a, b, c, d)  CONCAT4x(a, b, c, d)

#define FUNCTION_NAME(name, postfix) CONCAT2(name, postfix)

#define CLIP_MINMAX(x, min, max) (((x) > max) ? max : (((x) < min) ? min : (x)))

#define IS_POWER_OF_TWO(A) (((A) != 0) && ((((A) - 1) & (A)) == 0))

#define RETURN_IF(is_true, ret_val)        \
    do                                     \
    {                                      \
        if ((is_true)) { return ret_val; } \
    }                                      \
    while (0)

#endif /* _NEUTON_DEFINITIONS_H_ */