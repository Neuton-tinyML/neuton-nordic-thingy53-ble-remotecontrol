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

#ifndef _NEUTON_USER_DATA_PREPARATION_CONFIG_H_
#define _NEUTON_USER_DATA_PREPARATION_CONFIG_H_

/** User input features type */
#define NEUTON_NN_INPUT_TYPE NEUTON_NN_INPUT_TYPE_INT16

/** Number of unique features in the original input sample */
#define NEUTON_NN_INPUT_UNIQ_FEATURES_NUM 6

/** Number of unique features actually used by NN from the original input sample */
#define NEUTON_NN_INPUT_UNIQ_FEATURES_USED_NUM 6

/** Number of input feature samples that should be collected in the input window
 *  feature_sample = 1 * NEUTON_NN_INPUT_UNIQ_FEATURES_NUM
 */
#define NEUTON_NN_INPUT_FEATURE_WINDOW_SIZE 90

/** Number of input feature samples on that the input window is shifted */
#define NEUTON_NN_INPUT_FEATURE_WINDOW_SHIFT 30

/** Number of lag features used from input features window  */
#define NEUTON_NN_LAG_FEATURES_NUM 0

/** Determines if NN used only input unprocessed features for inference */
#define NEUTON_NN_USE_INPUT_FEATURES 0

/** Determines the presence of a unique scaling factors for each input(LAG) feature  */
#define NEUTON_NN_USE_UNIQ_INPUT_SCALING 0

/** The maximum number of extracted features that user used for all unique input features */
#define NEUTON_NN_EXTRACTED_FEATURES_NUM 79

/** Determines the presence of a unique mask for feature extraction for each unique input feature */
#define NEUTON_NN_USE_UNIQ_FEATURES_MASK 1

/** Determines if features use feature clipping */
#define NEUTON_NN_USE_FEATURE_CLIPPING 1


/** Defines statistical features to be used in the compiled library */
#define NEUTON_NN_FEATURES_EXTRACT_MIN 0
#define NEUTON_NN_FEATURES_EXTRACT_MAX 0
#define NEUTON_NN_FEATURES_EXTRACT_MIN_MAX 0
#define NEUTON_NN_FEATURES_EXTRACT_RANGE 1
#define NEUTON_NN_FEATURES_EXTRACT_MEAN 1
#define NEUTON_NN_FEATURES_EXTRACT_RMS 1
#define NEUTON_NN_FEATURES_EXTRACT_STD 1
#define NEUTON_NN_FEATURES_EXTRACT_ZCR 1
#define NEUTON_NN_FEATURES_EXTRACT_MCR 1
#define NEUTON_NN_FEATURES_EXTRACT_TCR 0
#define NEUTON_NN_FEATURES_EXTRACT_MAD 1
#define NEUTON_NN_FEATURES_EXTRACT_SKEW 0
#define NEUTON_NN_FEATURES_EXTRACT_KUR 0
#define NEUTON_NN_FEATURES_EXTRACT_MOMENTS 0
#define NEUTON_NN_FEATURES_EXTRACT_P2P_LF 0
#define NEUTON_NN_FEATURES_EXTRACT_P2P_HF 0
#define NEUTON_NN_FEATURES_EXTRACT_P2P_LF_HF 0
#define NEUTON_NN_FEATURES_EXTRACT_ABSMEAN 1
#define NEUTON_NN_FEATURES_EXTRACT_AMDF 1
#define NEUTON_NN_FEATURES_EXTRACT_P_SCR 1
#define NEUTON_NN_FEATURES_EXTRACT_N_SCR 0
#define NEUTON_NN_FEATURES_EXTRACT_PSOZ 1
#define NEUTON_NN_FEATURES_EXTRACT_PSOM 1
#define NEUTON_NN_FEATURES_EXTRACT_PSOS 1
#define NEUTON_NN_FEATURES_EXTRACT_CREST 0
#define NEUTON_NN_FEATURES_EXTRACT_RDS 1
#define NEUTON_NN_FEATURES_EXTRACT_AUTOCORR 0
#define NEUTON_NN_FEATURES_EXTRACT_HJ_MOBILITY 0
#define NEUTON_NN_FEATURES_EXTRACT_HJ_COMPLEXITY 0

/** Defines spectral features to be used in the compiled library */
#define NEUTON_NN_FEATURES_EXTRACT_DOM_FREQS 0
#define NEUTON_NN_FEATURES_EXTRACT_DOM_FREQS_AMPL 0
#define NEUTON_NN_FEATURES_EXTRACT_DOM_FREQS_THD 0
#define NEUTON_NN_FEATURES_EXTRACT_DOM_FREQS_SNR 0
#define NEUTON_NN_FEATURES_EXTRACT_DOM_FREQS_MADF 0
#define NEUTON_NN_FEATURES_EXTRACT_FER_LOWMID 0
#define NEUTON_NN_FEATURES_EXTRACT_FER_MIDHIGH 0
#define NEUTON_NN_FEATURES_EXTRACT_FER_LOWHIGH 0
#define NEUTON_NN_FEATURES_EXTRACT_SPECTRAL_RMS 0
#define NEUTON_NN_FEATURES_EXTRACT_SPECTRAL_CREST 0
#define NEUTON_NN_FEATURES_EXTRACT_SPECTRAL_CENTROID 0
#define NEUTON_NN_FEATURES_EXTRACT_SPECTRAL_SPREAD 0
#define NEUTON_NN_FEATURES_EXTRACT_AMPL_SPECTRUM 0
#define NEUTON_NN_FEATURES_AMPL_SPECTRUM_LEN 0

#endif /* _NEUTON_USER_DATA_PREPARATION_CONFIG_H_ */
