#ifndef _NEUTON_NN_DSP_PIPELINE_TYPES_H_
#define _NEUTON_NN_DSP_PIPELINE_TYPES_H_

#include <neuton/neuton_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Possible NN features domain for feature extraction
 */
typedef enum neuton_nn_features_domain_e
{
    NEUTON_NN_FEATURES_DOMAIN_TIME, /**< Time-domain features */
    NEUTON_NN_FEATURES_DOMAIN_FREQ, /**< Frequency-domain features */
} neuton_nn_features_domain_t;

/**
 * @brief Time-domain features ID, should be kept in the same order as in neuton_nn_features_stat_mask_t
 */
typedef enum neuton_nn_feature_timedomain_e
{
    NEUTON_NN_FEATURE_MIN = 0,       /**< Minimum */
    NEUTON_NN_FEATURE_MAX,           /**< Maximum */
    NEUTON_NN_FEATURE_RANGE,         /**< Range */
    NEUTON_NN_FEATURE_MEAN,          /**< Mean */
    NEUTON_NN_FEATURE_MAD,           /**< Mean Absolute Deviation */
    NEUTON_NN_FEATURE_SKEW,          /**< Skewness */
    NEUTON_NN_FEATURE_KUR,           /**< Kurtosis */
    NEUTON_NN_FEATURE_STD,           /**< Standard Deviation */
    NEUTON_NN_FEATURE_RMS,           /**< Root Mean Square */
    NEUTON_NN_FEATURE_MCR,           /**< Mean-crossing Rate */
    NEUTON_NN_FEATURE_ZCR,           /**< Zero-crossing Rate */
    NEUTON_NN_FEATURE_TCR,           /**< Threshold-crossing Rate */
    NEUTON_NN_FEATURE_P2P_LF,        /**< Peak-to-Peak Low Frequency */
    NEUTON_NN_FEATURE_P2P_HF,        /**< Peak-to-Peak High Frequency */
    NEUTON_NN_FEATURE_ABSMEAN,       /**< Absolute mean */
    NEUTON_NN_FEATURE_AMDF,          /**< Average magnitude difference */
    NEUTON_NN_FEATURE_PSCR,          /**< Positive sigma crossing rate */
    NEUTON_NN_FEATURE_NSCR,          /**< Negative sigma crossing rate */
    NEUTON_NN_FEATURE_PSOZ,          /**< Percentage of signal over zero */
    NEUTON_NN_FEATURE_PSOM,          /**< Percentage of signal over mean */
    NEUTON_NN_FEATURE_PSOS,          /**< Percentage of signal over sigma */
    NEUTON_NN_FEATURE_CREST,         /**< Crest factor */
    NEUTON_NN_FEATURE_RMDS,          /**< Root Mean Difference Square */
    NEUTON_NN_FEATURE_AUTOCORR,      /**< Autocorrelation */
    NEUTON_NN_FEATURE_HJ_MOBILITY,   /**< Hjorth Mobility */
    NEUTON_NN_FEATURE_HJ_COMPLEXITY, /**< Hjorth Complexity */
    NEUTON_NN_FEATURE_LR_SLOPE,      /**< Linear regression Slope */
    NEUTON_NN_FEATURE_LR_INTERCEPT,  /**< Linear regression Intercept */

    NEUTON_NN_FEATURE_cnt, /**< Number of time-domain features */
} neuton_nn_feature_timedomain_t;

/** Bit position in time-domain feature extraction mask */
#define NEUTON_NN_FEATURE_BIT_MIN           (1U << NEUTON_NN_FEATURE_MIN)
#define NEUTON_NN_FEATURE_BIT_MAX           (1U << NEUTON_NN_FEATURE_MAX)
#define NEUTON_NN_FEATURE_BIT_RANGE         (1U << NEUTON_NN_FEATURE_RANGE)
#define NEUTON_NN_FEATURE_BIT_MEAN          (1U << NEUTON_NN_FEATURE_MEAN)
#define NEUTON_NN_FEATURE_BIT_RMS           (1U << NEUTON_NN_FEATURE_RMS)
#define NEUTON_NN_FEATURE_BIT_STD           (1U << NEUTON_NN_FEATURE_STD)
#define NEUTON_NN_FEATURE_BIT_ZCR           (1U << NEUTON_NN_FEATURE_ZCR)
#define NEUTON_NN_FEATURE_BIT_MCR           (1U << NEUTON_NN_FEATURE_MCR)
#define NEUTON_NN_FEATURE_BIT_TCR           (1U << NEUTON_NN_FEATURE_TCR)
#define NEUTON_NN_FEATURE_BIT_MAD           (1U << NEUTON_NN_FEATURE_MAD)
#define NEUTON_NN_FEATURE_BIT_SKEW          (1U << NEUTON_NN_FEATURE_SKEW)
#define NEUTON_NN_FEATURE_BIT_KUR           (1U << NEUTON_NN_FEATURE_KUR)
#define NEUTON_NN_FEATURE_BIT_P2P_LF        (1U << NEUTON_NN_FEATURE_P2P_LF)
#define NEUTON_NN_FEATURE_BIT_P2P_HF        (1U << NEUTON_NN_FEATURE_P2P_HF)
#define NEUTON_NN_FEATURE_BIT_ABSMEAN       (1U << NEUTON_NN_FEATURE_ABSMEAN)
#define NEUTON_NN_FEATURE_BIT_AMDF          (1U << NEUTON_NN_FEATURE_AMDF)
#define NEUTON_NN_FEATURE_BIT_POSITIVE_SCR  (1U << NEUTON_NN_FEATURE_PSCR)
#define NEUTON_NN_FEATURE_BIT_NEGATIVE_SCR  (1U << NEUTON_NN_FEATURE_NSCR)
#define NEUTON_NN_FEATURE_BIT_PSOZ          (1U << NEUTON_NN_FEATURE_PSOZ)
#define NEUTON_NN_FEATURE_BIT_PSOM          (1U << NEUTON_NN_FEATURE_PSOM)
#define NEUTON_NN_FEATURE_BIT_PSOS          (1U << NEUTON_NN_FEATURE_PSOS)
#define NEUTON_NN_FEATURE_BIT_CREST         (1U << NEUTON_NN_FEATURE_CREST)
#define NEUTON_NN_FEATURE_BIT_RMDS          (1U << NEUTON_NN_FEATURE_RMDS)
#define NEUTON_NN_FEATURE_BIT_AUTOCORR      (1U << NEUTON_NN_FEATURE_AUTOCORR)
#define NEUTON_NN_FEATURE_BIT_HJ_MOBILITY   (1U << NEUTON_NN_FEATURE_HJ_MOBILITY)
#define NEUTON_NN_FEATURE_BIT_HJ_COMPLEXITY (1U << NEUTON_NN_FEATURE_HJ_COMPLEXITY)
#define NEUTON_NN_FEATURE_BIT_LR_SLOPE      (1U << NEUTON_NN_FEATURE_LR_SLOPE)
#define NEUTON_NN_FEATURE_BIT_LR_INTERCEPT  (1U << NEUTON_NN_FEATURE_LR_INTERCEPT)

/**
 * @brief Frequency-domain features ID, should be kept in the same order as in neuton_nn_features_spectral_mask_t
 */
typedef enum neuton_nn_feature_freqdomain_e
{
    NEUTON_NN_FEATURE_DOM_FREQS = 0,       /**< Dominant frequencies in spectrum */
    NEUTON_NN_FEATURE_DOM_FREQS_AMPL,      /**< Amplitudes of dominant frequencies in spectrum */
    NEUTON_NN_FEATURE_DOM_FREQS_THD,       /**< Total harmonic distortion of dominant frequencies */
    NEUTON_NN_FEATURE_DOM_FREQS_SNR,       /**< Signal-to-noise ratio of dominant frequencies */
    NEUTON_NN_FEATURE_DOM_FREQS_MEAN_DIST, /**< Mean distance between dominant frequencies peaks */
    NEUTON_NN_FEATURE_FER_LOWMID,          /**< Frequencies energy ratio low/mid */
    NEUTON_NN_FEATURE_FER_MIDHIGH,         /**< Frequencies energy ratio mid/high */
    NEUTON_NN_FEATURE_FER_LOWHIGH,         /**< Frequencies energy ratio low/high */
    NEUTON_NN_FEATURE_SPECTRAL_RMS,        /**< Spectral RMS */
    NEUTON_NN_FEATURE_SPECTRAL_CREST,      /**< Spectral Crest */
    NEUTON_NN_FEATURE_SPECTRAL_CENTROID,   /**< Spectral Centroid */
    NEUTON_NN_FEATURE_SPECTRAL_SPREAD,     /**< Spectral Spread */
    NEUTON_NN_FEATURE_SPECTRUM_BINS,       /**< Amplitude spectrum raw bins */
} neuton_nn_feature_freqdomain_t;

/** Bit position in frequency-domain feature extraction mask */
#define NEUTON_NN_FEATURE_BIT_DOM_FREQS           (1U << NEUTON_NN_FEATURE_DOM_FREQS)
#define NEUTON_NN_FEATURE_BIT_DOM_FREQS_AMPL      (1U << NEUTON_NN_FEATURE_DOM_FREQS_AMPL)
#define NEUTON_NN_FEATURE_BIT_DOM_FREQS_THD       (1U << NEUTON_NN_FEATURE_DOM_FREQS_THD)
#define NEUTON_NN_FEATURE_BIT_DOM_FREQS_SNR       (1U << NEUTON_NN_FEATURE_DOM_FREQS_SNR)
#define NEUTON_NN_FEATURE_BIT_DOM_FREQS_MEAN_DIST (1U << NEUTON_NN_FEATURE_DOM_FREQS_MEAN_DIST)
#define NEUTON_NN_FEATURE_BIT_FER_LOWMID          (1U << NEUTON_NN_FEATURE_FER_LOWMID)
#define NEUTON_NN_FEATURE_BIT_FER_MIDHIGH         (1U << NEUTON_NN_FEATURE_FER_MIDHIGH)
#define NEUTON_NN_FEATURE_BIT_FER_LOWHIGH         (1U << NEUTON_NN_FEATURE_FER_LOWHIGH)
#define NEUTON_NN_FEATURE_BIT_SPECTRAL_RMS        (1U << NEUTON_NN_FEATURE_SPECTRAL_RMS)
#define NEUTON_NN_FEATURE_BIT_SPECTRAL_CREST      (1U << NEUTON_NN_FEATURE_SPECTRAL_CREST)
#define NEUTON_NN_FEATURE_BIT_SPECTRAL_CENTROID   (1U << NEUTON_NN_FEATURE_SPECTRAL_CENTROID)
#define NEUTON_NN_FEATURE_BIT_SPECTRAL_SPREAD     (1U << NEUTON_NN_FEATURE_SPECTRAL_SPREAD)
#define NEUTON_NN_FEATURE_BIT_SPECTRUM_BINS       (1U << NEUTON_NN_FEATURE_SPECTRUM_BINS)

/**
 * @brief Time-domain features mask type for feature extracting API
 */
typedef union neuton_nn_features_timedomain_mask_u
{
    struct
    {
        bool min          : 1; /**< Minimum */
        bool max          : 1; /**< Maximum */
        bool range        : 1; /**< Range */
        bool mean         : 1; /**< Mean */
        bool mad          : 1; /**< Mean Absolute Deviation */
        bool skew         : 1; /**< Skewness */
        bool kur          : 1; /**< Kurtosis */
        bool std          : 1; /**< Standard Deviation */
        bool rms          : 1; /**< Root Mean Square */
        bool mcr          : 1; /**< Mean-crossing Rate */
        bool zcr          : 1; /**< Zero-crossing Rate */
        bool tcr          : 1; /**< Threshold-crossing Rate */
        bool p2p_lf       : 1; /**< Peak-to-Peak Low Frequency */
        bool p2p_hf       : 1; /**< Peak-to-Peak High Frequency */
        bool absmean      : 1; /**< Absolute mean */
        bool amdf         : 1; /**< Average magnitude difference */
        bool p_scr        : 1; /**< Positive sigma crossing rate */
        bool n_scr        : 1; /**< Negative sigma crossing rate */
        bool psoz         : 1; /**< Percentage of signal over zero */
        bool psom         : 1; /**< Percentage of signal over mean */
        bool psos         : 1; /**< Percentage of signal over sigma */
        bool crest        : 1; /**< Crest factor */
        bool rmds         : 1; /**< Root Mean Difference Square */
        bool autocorr     : 1; /**< Autocorrelation */
        bool hjorth_m     : 1; /**< Hjorth Mobility */
        bool hjorth_c     : 1; /**< Hjorth Complexity */
        bool lr_slope     : 1; /**< Linear regression Slope */
        bool lr_intercept : 1; /**< Linear regression Intercept */
    } is;
    neuton_u32_t all; /**< All time-domain features as bitmask */
} neuton_nn_features_timedomain_mask_t;

/**
 * @brief Frequency-domain features mask type for feature extracting API
 */
typedef union neuton_nn_features_freqdomain_mask_u
{
    struct
    {
        bool dom_freqs        : 1; /**< Dominant frequencies indicies in spectrum */
        bool dom_freqs_ampl   : 1; /**< Dominant frequencies amplitude values in spectrum */
        bool dom_freqs_thd    : 1; /**< Dominant frequencies total harmonic distortion */
        bool dom_freqs_snr    : 1; /**< Dominant frequencies SNR */
        bool dom_freqs_mean_d : 1; /**< Dominant frequencies mean distance */
        bool fer_lowmid       : 1; /**< Frequencies energy ratio Low / Mid */
        bool fer_midhigh      : 1; /**< Frequencies energy ratio Mid / High */
        bool fer_lowhigh      : 1; /**< Frequencies energy ratio Low / High */
        bool rms              : 1; /**< Spectral RMS */
        bool crest            : 1; /**< Spectral Crest */
        bool centroid         : 1; /**< Spectral Centriod */
        bool spread           : 1; /**< Spectral Spread */
        bool ampl_spectrum    : 1; /**< Amplitude spectrum N first bins */
    } is;
    neuton_u16_t all; /**< All frequency-domain features as bitmask */
} neuton_nn_features_freqdomain_mask_t;

/**
 * @brief Mask for all avaliable features for feature extraction
 */
typedef union neuton_nn_features_mask_u
{
    struct
    {
        neuton_nn_features_freqdomain_mask_t freq;  /**< Frequency-domain features mask */
        neuton_u16_t                         dummy; /**< Dummy 2 bytes for proper memory aligment */
        neuton_nn_features_timedomain_mask_t time;  /**< Time-domain features mask */
    } domain;
    neuton_u64_t all; /**< All features as bitmask */
} neuton_nn_features_mask_t;

/**
 * @brief Callback for getting feature argument while feature extraction
 *
 * @param[in] domain               Features domain (time/freq)
 * @param[in] feature_id           Feature id for which argument is needed
 * @param[in] args_num             Numbers of arguments to get
 * @param[in] p_argument_ctx       Argument user context
 * @param[out] p_output_arguments  Pointer to store feature argument
 */
typedef void (*neuton_nn_feature_get_arg_cb_t)(neuton_nn_features_domain_t domain,
                                               neuton_u8_t                 feature_id,
                                               neuton_u8_t                 args_num,
                                               void*                       p_argument_ctx,
                                               void*                       p_output_arguments);

/**
 * @brief Pipeline function type for 8-bit integer input
 */
typedef neuton_sz_t (*neuton_nn_features_pipeline_func_i8_t)(
    neuton_i8_t*                    p_input,
    neuton_sz_t                     num,
    neuton_i16_t*                   p_features,
    const neuton_nn_features_mask_t feature_mask,
    void*                           p_ctx,
    neuton_nn_feature_get_arg_cb_t  get_argument,
    void*                           p_argument_ctx);

/**
 * @brief Pipeline function type for 16-bit integer input
 */
typedef neuton_sz_t (*neuton_nn_features_pipeline_func_i16_t)(
    neuton_i16_t*                   p_input,
    neuton_sz_t                     num,
    neuton_i32_t*                   p_features,
    const neuton_nn_features_mask_t feature_mask,
    void*                           p_ctx,
    neuton_nn_feature_get_arg_cb_t  get_argument,
    void*                           p_argument_ctx);

/**
 * @brief Pipeline function type for 32-bit float input
 */
typedef neuton_sz_t (*neuton_nn_features_pipeline_func_f32_t)(
    neuton_f32_t*                   p_input,
    neuton_sz_t                     num,
    neuton_f32_t*                   p_features,
    const neuton_nn_features_mask_t feature_mask,
    void*                           p_ctx,
    neuton_nn_feature_get_arg_cb_t  get_argument,
    void*                           p_argument_ctx);

/**
 * @brief Union of pipeline function pointers for all supported input types
 */
typedef union neuton_nn_features_pipeline_u
{
    const void* p_void; /**< Generic pointer */
    const neuton_nn_features_pipeline_func_i8_t*
        p_array_i8; /**< Array of 8-bit pipeline functions */
    const neuton_nn_features_pipeline_func_i16_t*
        p_array_i16; /**< Array of 16-bit pipeline functions */
    const neuton_nn_features_pipeline_func_f32_t*
        p_array_f32; /**< Array of 32-bit pipeline functions */
} neuton_nn_features_pipeline_t;

/**
 * @brief Features pipeline context structure
 */
typedef struct neuton_nn_features_pipeline_ctx_s
{
    const neuton_nn_features_pipeline_t functions;     /**< Pipeline functions union */
    const neuton_sz_t functions_num; /**< Number of pipeline functions */
    void*             p_ctx;          /**< User context for pipeline functions */
} neuton_nn_features_pipeline_ctx_t;

/**
 * @brief Features meta information for 16-bit integer features
 */
typedef struct neuton_nn_features_meta_i16_s
{
    const neuton_i16_t* p_min;       /**< Pointer to minimum values */
    const neuton_i16_t* p_max;       /**< Pointer to maximum values */
    const neuton_i8_t*  p_arguments; /**< Pointer to feature arguments */
} neuton_nn_features_meta_i16_t;

/**
 * @brief Features meta information for 32-bit integer features
 */
typedef struct neuton_nn_features_meta_i32_s
{
    const neuton_i32_t* p_min;       /**< Pointer to minimum values */
    const neuton_i32_t* p_max;       /**< Pointer to maximum values */
    const neuton_i16_t* p_arguments; /**< Pointer to feature arguments */
} neuton_nn_features_meta_i32_t;

/**
 * @brief Features meta information for 32-bit float features
 */
typedef struct neuton_nn_features_meta_f32_s
{
    const neuton_f32_t* p_min;       /**< Pointer to minimum values */
    const neuton_f32_t* p_max;       /**< Pointer to maximum values */
    const neuton_f32_t* p_arguments; /**< Pointer to feature arguments */
} neuton_nn_features_meta_f32_t;

/**
 * @brief Union of features meta information for all supported types
 */
typedef union neuton_nn_features_meta_u
{
    neuton_nn_features_meta_i16_t i16; /**< Meta for 16-bit integer features */
    neuton_nn_features_meta_i32_t i32; /**< Meta for 32-bit integer features */
    neuton_nn_features_meta_f32_t f32; /**< Meta for 32-bit float features */
} neuton_nn_features_meta_t;

/**
 * @brief FFT context frequency-domain features extraction for 32-bit float input
 */
typedef struct neuton_nn_features_freq_fft_ctx_f32_s
{
    neuton_f32_t*       p_rfft_buffer;         /**< Pointer to FFT working buffer */
    const neuton_f32_t* p_rfft_twiddle_table; /**< Pointer to RFFT twiddle factors table */
    const neuton_f32_t* p_cfft_twiddle_table; /**< Pointer to CFFT twiddle factors table */
    const neuton_u16_t* p_cfft_bitrev_table; /**< Pointer to bit-reversal table */
    const neuton_u16_t  cfft_bitrev_table_len;  /**< Length of bit-reversal table */
    const neuton_u16_t  rfft_len;            /**< Length of RFFT */
} neuton_nn_features_freq_fft_ctx_f32_t;

/**
 * @brief FFT context frequency-domain features extraction for 16-bit integer input
 */
typedef struct neuton_nn_features_freq_fft_ctx_i16_s
{
    neuton_i16_t*       p_rfft_buffer;         /**< Pointer to FFT working buffer */
    const neuton_i16_t* p_rfft_twiddle_table; /**< Pointer to RFFT twiddle factors table */
    const neuton_i16_t* p_cfft_twiddle_table; /**< Pointer to CFFT twiddle factors table */
    const neuton_u16_t* p_cfft_bitrev_table; /**< Pointer to bit-reversal table */
    const neuton_u16_t  cfft_bitrev_table_len;  /**< Length of bit-reversal table */
    const neuton_u16_t  rfft_len;            /**< Length of RFFT */
} neuton_nn_features_freq_fft_ctx_i16_t;

/**
 * @brief Union of FFT contexts for all supported input types
 */
typedef union neuton_nn_features_freq_fft_ctx_u
{
    neuton_nn_features_freq_fft_ctx_f32_t f32; /**< FFT context for 32-bit float input */
    neuton_nn_features_freq_fft_ctx_i16_t i16; /**< FFT context for 16-bit integer input */
} neuton_nn_features_freq_fft_ctx_t;

/**
 * @brief DSP feature extraction context structure
 */
typedef struct neuton_nn_dsp_feature_extraction_s
{
    union
    {
        void*         p_void; /**< Generic pointer to extracted features memory */
        neuton_i16_t* p_i16;  /**< Pointer to 16-bit extracted features memory */
        neuton_i32_t* p_i32;  /**< Pointer to 32-bit extracted features memory */
        neuton_f32_t* p_f32;  /**< Pointer to 32-bit float extracted features memory */
    } extracted_memory;

    neuton_nn_features_meta_t meta; /**< Features meta information */

    const neuton_u16_t overall_num; /**< Overall number of extracted features */

    const neuton_u16_t masks_num; /**< Number of features masks in array */
    
    const neuton_nn_features_mask_t* p_masks; /**< Pointer to array of features mask */

    /**< Pointer to time-domain pipeline context */
    const neuton_nn_features_pipeline_ctx_t* p_timedomain_pipeline;

    /**< Pointer to freq-domain pipeline context */
    const neuton_nn_features_pipeline_ctx_t* p_freqdomain_pipeline;
} neuton_nn_dsp_feature_extraction_t;

/**
 * @brief DSP pipeline context structure
 */
typedef struct neuton_nn_dsp_pipeline_s
{
    neuton_nn_dsp_feature_extraction_t features; /**< DSP feature extraction context */
} neuton_nn_dsp_pipeline_t;

#ifdef __cplusplus
}
#endif

#endif /* _NEUTON_NN_DSP_PIPELINE_TYPES_H_ */