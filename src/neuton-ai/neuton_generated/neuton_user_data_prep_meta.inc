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

/** Defines input(also used for LAG) features MIN scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MIN[] = { -32768 };

/** Defines input(also used for LAG) features MAX scaling factor
 */
static const neuton_input_t INPUT_FEATURES_SCALE_MAX[] = { 32767 };

/** Defines which unique input features is used for LAG features processing,
 *  one bit for one unique feature, starting from LSB
 */
static const neuton_u8_t INPUT_FEATURES_USED_FOR_LAGS_MASK[] = { 0x00 };

/** Defines feature extraction masks used as neuton_nn_features_mask_t,
 *  64 bit for one unique input feature, @ref neuton_nn_features_mask_t to see bitmask
 */
static const neuton_u64_t FEATURES_EXTRACTION_MASK[] = { 0x005dc39c00000000,
     0x004dc39c00000000, 0x004cc79c00000000, 0x005dc79c00000000, 0x005dc79c00000000,
     0x005dc79c00000000 };

/** Defines arguments used while feature extraction
 */
static const neuton_input_t FEATURES_EXTRACTION_ARGUMENTS[] = { 1, 1, 1, 1, 1,
     1, 1, 1, 1 };

/** Defines extracted features MIN scaling factor
 */
static const neuton_feature_t EXTRACTED_FEATURES_SCALE_MIN[] = { 58, -12306,
     11, 16, 59, 11, 47, 12, 0, 0, 100, 0, 144, 72, -20827, 12, 16, 32, 11, 26,
     16, 0, 0, 122, 196, 82, -15043, 13, 22, 25, 11, 0, 20, 17, 0, 111, 210,
     16, -6661, 2, 4, 7, 11, 0, 5, 3, 0, 0, 88, 0, 44, 19, -6090, 3, 5, 11, 11,
     0, 8, 4, 0, 0, 122, 0, 53, 19, -8545, 3, 4, 7, 11, 0, 5, 3, 0, 0, 111, 0,
     38 };

/** Defines extracted features MAX scaling factor
 */
static const neuton_feature_t EXTRACTED_FEATURES_SCALE_MAX[] = { 65535, 19491,
     21725, 24403, 24595, 651, 22175, 6457, 337, 1000, 911, 411, 65477, 65535,
     16022, 18499, 20950, 21791, 573, 20827, 11364, 370, 1000, 933, 65356, 65535,
     15750, 14427, 16156, 18244, 573, 516, 15750, 7653, 1000, 833, 65200, 65535,
     7229, 18335, 20869, 21423, 617, 573, 18818, 3172, 325, 1000, 911, 333, 43897,
     65535, 6075, 22141, 24228, 24229, 584, 382, 22180, 4305, 303, 1000, 955,
     333, 63332, 65535, 7952, 22910, 24292, 24433, 640, 426, 23020, 4182, 359,
     1000, 888, 333, 55342 };

