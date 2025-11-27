#include <neuton/private/neuton_defs.h>

#ifndef FPEAKS_INPUT_TYPE
#error "FPEAKS_INPUT_TYPE is not defined!"
#endif

#ifndef FPEAKS_INPUT_T_MIN
#error "FPEAKS_INPUT_T_MIN is not defined!"
#endif

#define INPUT_T     CONCAT3(neuton, FPEAKS_INPUT_TYPE, t)
#define INPUT_T_MIN FPEAKS_INPUT_T_MIN

// ///////////////////////////////////////////////////////////////////////////

void FUNCTION_NAME(neuton_dsp_findpeaks, FPEAKS_INPUT_TYPE)(INPUT_T      p_input[],
                                                            neuton_u16_t num,
                                                            INPUT_T      min_peak_height,
                                                            neuton_u16_t min_peak_distance,
                                                            neuton_i16_t peaks_indices[],
                                                            neuton_u16_t peaks_indices_num)

{
    // Helper array to store peak values for easy comparison, initialized to very small values
    INPUT_T peak_values[peaks_indices_num];

    // Initialize peak indices array to invalid index (-1)
    for (neuton_u16_t i = 0; i < peaks_indices_num; i++)
    {
        peaks_indices[i] = -1;
        peak_values[i]   = INPUT_T_MIN;
    }

    neuton_i16_t last_peak_index = -min_peak_distance;  // To enforce min_peak_distance

    // Loop through the array to find peaks
    for (neuton_u16_t i = 1; i < num - 1; i++)
    {
        // Check if current value is a peak (larger than both neighbors)
        if (p_input[i] > p_input[i - 1] && p_input[i] > p_input[i + 1])
        {
            // Check if it satisfies the min_peak_height condition
            if (p_input[i] >= min_peak_height)
            {
                // Enforce min_peak_distance: Skip if too close to the last peak
                if (i - last_peak_index >= min_peak_distance)
                {
                    // Check if this peak is higher than any of the current highest peaks
                    for (neuton_u16_t j = 0; j < peaks_indices_num; j++)
                    {
                        if (p_input[i] > peak_values[j])
                        {
                            // Shift smaller peaks down the list
                            for (neuton_u16_t k = peaks_indices_num - 1; k > j; k--)
                            {
                                peak_values[k]   = peak_values[k - 1];
                                peaks_indices[k] = peaks_indices[k - 1];
                            }
                            // Insert the new peak
                            peak_values[j]   = p_input[i];
                            peaks_indices[j] = i;
                            break;
                        }
                    }
                    last_peak_index = i;
                }
            }
        }
    }
}