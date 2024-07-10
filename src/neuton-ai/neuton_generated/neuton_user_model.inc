/* 2024-07-09T15:25:11Z */

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


static const neuton_weight_t MODEL_WEIGHTS[] = { -7401, 13914, 32763, -6046,
     -32650, 30028, 32524, -3292, 32766, 32763, 7111, 28900, -8125, 32764, -24595,
     2163, 7738, -10988, 11126, -2335, 1608, 7764, -12598, 31040, -19110, -13618,
     16645, -3109, -1199, -26426, -3921, -13086, 22524, 26586, 6409, -21586,
     -17110, 5597, -32742, 19131, 22626, -21029, 2059, 20728, 11375, 8262, 16286,
     12182, 5790, -9328, 32764, 22129, -31923, 32765, 28718, -9757, -18819, 20804,
     15370, -31521, -19166, 30113, 13603, -11641, 1374, -22727, 32767, -7307,
     -24660, 2358, 26347, 6422, -23461, 25528, -15937, -30129, 14018, -31022,
     1916, 32101, 25315, -5784, -9927, -23502, 10306, 32767, -22337, -10526,
     23779, 6467, -13962, 2656, 29231, 32766, 32384, 29734, -2680, 25143, -346,
     15715, -12290, -2918, 32765, 32528, -23776, 18732, 27568, 28236, -3564,
     32765, 11179, -23799, 11250, 24618, 5585, -6563, -32659, 11617, -16574,
     -32017, 322, -5892, 3053, 17892, 8367, 4631, -4756, 14113, 3428, 27747,
     -188, 15126, 11119, 9037, -16383, -32766, -22422, -32768, 32766, 1631, 31724,
     -9744, 32765, 32767, -16114, 32766, -12645, -32768, -32768, 21292, -32766,
     2695, 32766, 12631, 9809, -17148, -2178, 32765, -32768, -8679, -16009, 32553,
     32766, 2993, 8029, 25829, 16383, 28732, 32767, -32592, 32766, 2879, -29122,
     -32768, 21382, -28258, 19790, 23479, 13460, 32465, -17727, 11680, -28806,
     -32768, -32768, 8477, 6479, -31138, -26818, 8443, 9583, -8451, -1060, 325,
     -9489, 9472, -10801, 17917, -3818, -32768, 32766, -12, 1331, 4752, -32766,
     -3661, 20376, -27057, -32766, 2937, -11833, 22932, -17513, -31973, 32765,
     -32768, 9854 };

static const neuton_sources_num_t MODEL_LINKS[] = { 0, 1, 18, 24, 29, 30, 33,
     35, 48, 49, 50, 52, 2, 5, 6, 7, 11, 12, 15, 17, 20, 25, 32, 46, 50, 52,
     1, 0, 17, 19, 21, 33, 38, 39, 45, 47, 52, 0, 1, 2, 2, 4, 8, 12, 13, 15,
     18, 21, 23, 27, 38, 39, 41, 45, 51, 52, 0, 3, 4, 6, 10, 11, 14, 17, 18,
     19, 20, 22, 26, 28, 30, 37, 41, 42, 43, 44, 47, 52, 0, 5, 6, 7, 9, 11, 12,
     19, 20, 22, 25, 26, 27, 36, 39, 48, 49, 52, 1, 1, 2, 4, 5, 8, 9, 12, 13,
     16, 30, 31, 33, 42, 45, 52, 6, 6, 8, 13, 31, 52, 1, 4, 6, 0, 2, 7, 11, 12,
     17, 35, 52, 1, 0, 5, 10, 15, 40, 41, 52, 0, 9, 52, 2, 52, 2, 11, 52, 3,
     52, 3, 13, 52, 4, 5, 9, 1, 29, 43, 52, 4, 15, 52, 1, 5, 9, 6, 10, 15, 19,
     25, 44, 46, 48, 52, 5, 17, 52, 7, 5, 16, 29, 31, 33, 51, 52, 6, 19, 52,
     2, 7, 8, 19, 1, 7, 9, 15, 21, 31, 34, 40, 52, 7, 21, 52, 1, 6, 8, 17, 10,
     12, 17, 22, 24, 46, 52, 1, 8, 23, 52 };

static const neuton_weights_num_t MODEL_INTERNAL_LINKS_BOUNDARIES[] = { 0, 12,
     27, 40, 56, 78, 97, 113, 121, 130, 139, 141, 144, 146, 149, 153, 159, 163,
     174, 176, 185, 190, 201, 206, 216 };

static const neuton_weights_num_t MODEL_EXTERNAL_LINKS_BOUNDARIES[] = { 12, 26,
     37, 56, 78, 96, 112, 118, 129, 137, 140, 142, 145, 147, 150, 157, 160, 172,
     175, 183, 186, 199, 202, 213, 217 };

static const neuton_coeff_t MODEL_ACTIVATION_COEFFS[] = { 0, 0, 0, 0, 0, 0, 0,
     0, 11264, 64512, 40959, 60416, 40959, 63488, 40960, 60416, 40955, 16384,
     40960, 0, 40960, 60416, 40954, 64512, 40959 };

static const neuton_u8_t MODEL_ACTIVATION_TYPE_MASK[] = { 0xff, 0xab, 0xaa, 0x00 };

static const neuton_neurons_num_t MODEL_OUTPUT_NEURONS[] = { 10, 24, 12, 14,
     16, 18, 20, 22 };

