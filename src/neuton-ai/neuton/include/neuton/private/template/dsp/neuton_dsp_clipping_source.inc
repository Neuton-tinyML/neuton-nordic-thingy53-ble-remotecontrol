#include <neuton/private/neuton_defs.h>

#ifndef CLIPPING_INPUT_TYPE
    #error "CLIPPING_INPUT_TYPE is not defined!"
#endif

#define INPUT_T     CONCAT3(neuton, CLIPPING_INPUT_TYPE, t)

// ///////////////////////////////////////////////////////////////////////////

void FUNCTION_NAME(neuton_dsp_clip, CLIPPING_INPUT_TYPE)
                   (INPUT_T* p_input, neuton_u16_t num,
                    const INPUT_T min, const INPUT_T max)
{
    INPUT_T new_val;
    neuton_u16_t loop_cnt = num;

    while (loop_cnt > 0U)
    {
        new_val = *p_input;

        if (new_val > max)
            *p_input = max;
        else if (new_val < min)
            *p_input = min;

        p_input++;
        loop_cnt--;
    }
}