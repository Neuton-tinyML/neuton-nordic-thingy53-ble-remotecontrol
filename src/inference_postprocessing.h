/* 2023-06-09T11:22:25Z */

/* ----------------------------------------------------------------------
Copyright (c) 2022-2024 Neuton.AI, Inc.
*
The source code and its binary form are being made available on the following terms:
Redistribution, use, and modification are permitted provided that the following
conditions are met:
*
1. Redistributions of source code and/or its binary form must retain the above copyright notice,
* this list of conditions (and the disclaimer) either in the body of the source code or in
* the documentation and/or other materials provided with the distribution of the binary form, as
applicable.
*
2. The name of the copyright holder may not be used to endorse or promote products derived from this
* source code or its binary form without specific prior written permission of Neuton.AI, Inc.
*
3. Disclaimer. THIS SOURCE CODE AND ITS BINARY FORM ARE PROVIDED BY THE COPYRIGHT HOLDER "AS IS".
* THE COPYRIGHT HOLDER HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE HELD LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS
* OF THIRD PARTIES; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOURCE CODE OR ITS BINARY FORM, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------- */
#ifndef INFERENCE_POSTPROCESSING_H__
#define INFERENCE_POSTPROCESSING_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    CLASS_LABEL_UNKNOWN = 0,            ///< CLASS_LABEL_UNKNOWN
    CLASS_LABEL_SWIPE_UP = 1,           ///< CLASS_LABEL_SWIPE_UP
    CLASS_LABEL_SWIPE_DOWN = 2,         ///< CLASS_LABEL_SWIPE_DOWN
    CLASS_LABEL_SWIPE_LEFT = 3,         ///< CLASS_LABEL_SWIPE_LEFT
    CLASS_LABEL_SWIPE_RIGHT = 4,        ///< CLASS_LABEL_SWIPE_RIGHT
    CLASS_LABEL_DOUBLE_THUMB = 5,       ///< CLASS_LABEL_DOUBLE_THUMB
    CLASS_LABEL_DOUBLE_SHAKE = 6,       ///< CLASS_LABEL_DOUBLE_SHAKE
    CLASS_LABEL_ROTATION_RIGHT = 7,     ///< CLASS_LABEL_ROTATION_RIGHT
    CLASS_LABEL_ROTATION_LEFT = 8,      ///< CLASS_LABEL_ROTATION_LEFT
    CLASS_LABEL_IDLE = 9                ///< CLASS_LABEL_IDLE
} class_label_t;

/**
 * @brief Inference Result (prediction) postprocessing callback
 * 
 * @param[in] class_label   Label of the predicted class @ref class_label_t
 * @param[in] probability   Probability of the predicted class   
 * @param[in] class_name    Name of predicted class, null-terminated string
 * @param[in] is_raw        If true the postprocessing logic was not applied to this prediction
 * 
 */
typedef void (*inference_postprocess_cb_t)(const class_label_t class_label, 
                                            const float probability,
                                            const char* class_name,
                                            const bool is_raw);

/**
 * @brief Postprocess the Neuton library RAW inference output
 * 
 * @param[in] predicted_target  Predicted target(class)
 * @param[in] probability       Predicted probability of the target
 * @param[in] do_postprocessing If false, no postprocessing is applied and the raw prediction goes to the user callback unchanged
 * @param[in] callback          Inference Result (prediction) ready user callback, @ref inference_postprocess_cb_t 
 */
void inference_postprocess(const uint16_t predicted_target,
                            const float probability,
                            const bool do_postprocessing,
                            inference_postprocess_cb_t callback);



#endif /* INFERENCE_POSTPROCESSING_H__ */
