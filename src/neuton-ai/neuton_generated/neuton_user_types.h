/* 2025-01-13T13:20:24Z */

/* ----------------------------------------------------------------------
Copyright (c) 2022-2023 Neuton.AI, Inc.
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

#ifndef _NEUTON_NN_USER_TYPES_H_
#define _NEUTON_NN_USER_TYPES_H_

#include <neuton/neuton_types.h>

#ifdef   __cplusplus
extern "C"
{
#endif

typedef neuton_i16_t neuton_input_t;
typedef neuton_f32_t neuton_output_t;
typedef neuton_i32_t neuton_feature_t;
typedef neuton_u16_t neuton_coeff_t;
typedef neuton_i64_t neuton_accum_t;
typedef neuton_i16_t neuton_weight_t;
typedef neuton_u8_t neuton_sources_num_t;
typedef neuton_u16_t neuton_weights_num_t;
typedef neuton_i32_t neuton_2x_q_t;
typedef neuton_u8_t neuton_neurons_num_t;

#ifdef   __cplusplus
}
#endif

#endif /* _NEUTON_NN_USER_TYPES_H_ */
