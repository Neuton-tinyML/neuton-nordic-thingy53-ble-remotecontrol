# Neuton C Library

Neuton is an unique neural network framework, natively creates incredibly compact and accurate TinyML models that can easily be deployed into your firmware project using an automatically generated archive with a C library.

The Neuton library is static C library, written in accordance with the C99 standard and has no dependencies other than the standard C language library (libc). Our library does not use any hardware-specific instructions, dynamic memory allocation, stack usage is kept to a minimum.

# How to integrate Neuton into your firmware project 

> **IMPORTANT**  
> If your account is on the Zero Gravity plan, the generated library will have a time limit for model inference. When creating a solution on the platform `neuton.ai`, you specified the frequency of data collection, then the limit will be about 30 minutes of inferences; if you did not specify, then the limit will be 1800 model inferences per power cycle of the device. For more information, please contact support@neuton.ai!

## Neuton folder structure

There are only two folders that should be added to your project for integrating Neuton:
 * `neuton` - main framework folder with all Neuton source code and binaries:
    * `neuton/lib` -  folder with precompiled libraries for different architectures, e.g. `libneuton_arm_cm4.a`.
    * `neuton/include` - folder with all header files and interfaces for library usage.
 * `neuton_generated` - folder containing all user solution-specific files (neural network model, data preprocessing configuration, etc).

1. Link Neuton C static library for your device architecture to your firmware project.
2. Add `./neuton/include` folder to your project global INCLUDE paths.
3. Add folder where  `./neuton_generated` **is located** (not this folder itself) to your project global INCLUDE paths.

## Use Neuton in your project

First of all, you need to include the main header file of Neuton:
``` C
#include <neuton/neuton.h>
```
For making an inference with Neuton, there are only 3 functions that you should use:
* `neuton_nn_setup` - Set up the internal components of Neuton, should be called first and once;
* `neuton_nn_feed_inputs` - Feed and prepare live input features for model inference;
* `neuton_nn_run_inference` - Run live input features into a Neuton machine learning algorithm (or “ML model”) to inference an output;

### How to feed input data (raw features / sensor data)

Collect the array of the input data, for example the input data can be sensor data or any type of signal data. The number of samples in the input data array and their order should be **the same** as in the training dataset (for example Accelerometer_X, Accelerometer_Y, Accelerometer_Z).

Pass the array of raw input data to the `neuton_nn_feed_inputs` function.
``` C
// In this example, our raw features are the 3 accelerometer axis values
// The number of raw features and their order should be the same as in the training dataset file
neuton_input_t raw_features[] = 
{
    Accelerometer_X,
    Accelerometer_Y,
    Accelerometer_Z
};

// Setup Neuton library, should be called once
neuton_nn_setup();

// Feed raw input features to prepare them for model inference
uint32_t number_of_features = neuton_nn_uniq_inputs_num(); // Will be equal to 3

neuton_input_features_t* p_input_features = neuton_nn_feed_inputs(raw_features, number_of_features);

// Check if input data is prepared and ready for model inference
if (p_input_features != NULL)
{
    //make inference
}
```
In case the Neuton solution needs to collect a data window, you can use the following sample-by-sample feed algorithm:
``` C
// In this example, our raw features is a window of N elements with 3 accelerometer axis values
// The number of raw features and their order should be the same as in the training dataset file
neuton_input_t raw_features[] = 
{
    Accelerometer_X0,
    Accelerometer_Y0,
    Accelerometer_Z0,
    /* ... */
    Accelerometer_Xn,
    Accelerometer_Yn,
    Accelerometer_Zn,
};

// Setup Neuton library, should be called once
neuton_nn_setup();

// Feed raw input features sample-by-sample to prepare them for model inference
uint32_t number_of_features = neuton_nn_uniq_inputs_num(); // Will be equal to 3
uint32_t window_size_of_features = neuton_nn_input_window_size(); // Will be equal to N
neuton_input_t* p_raw_features_begin = &raw_features[0];

for (size_t i = 0; i < window_size_of_features; i++)
{
    neuton_input_features_t* p_input_features = neuton_nn_feed_inputs(p_raw_features_begin, number_of_features);

    // Check if input data is prepared and ready for model inference
    if (p_input_features != NULL)
    {
        //make inference
        break;
    }
    // Shift pointer to raw features buffer by number_of_features
    p_raw_features_begin += number_of_features;
}
```

###	How to Run Model Inference

When input features is ready for running inference, you should call `neuton_nn_run_inference` function with three arguments:

``` C
/**
 * @brief Running live input features into a Neuton machine learning algorithm (or “ML model”) to inference an output
 * 
 * @param[in]  p_input_features     Input features for model inference, obtained from @ref neuton_nn_feed_inputs() API call
 * 
 * @param[out] p_index              For Classification: Index of predicted target(class) with highest probability. 
 *                                  For Regression and Anomaly detection: p_index is not used and always 0
 * 
 * @param[out] pp_outputs           Pointer to the internal buffer with all model outputs.
 *                                  For Classification: contains probabilities of each class (binary/multi classification)
 *                                  For Regression: contains predicted target values
 *                                  For Anomaly detection: contains anomaly score
 * 
 * @return neuton_i16_t       Number of the predicted outputs(classes/values/anomaly score) or the following errors:
 *                                  NEUTON_NN_ERR_INVALID_ARGUMENT      if p_input_features is invalid,
 *                                  NEUTON_NN_ERR_FREE_LIMIT_EXPIRED    if you are using the free version and the number of available inferences has expired,
 *                                                                      for more information please contact us! 
 */
neuton_i16_t neuton_nn_run_inference(neuton_input_features_t* p_input_features, 
                                    neuton_u16_t* p_index, 
                                    const neuton_output_t** pp_outputs);
```

### Wrapping everything together for Classification

``` C
// In this example, our raw features is a window of N elements with 3 accelerometer axis values
// The number of raw features and their order should be the same as in the training dataset file
neuton_input_t raw_features[] = 
{
    Accelerometer_X0,
    Accelerometer_Y0,
    Accelerometer_Z0,
    /* ... */
    Accelerometer_Xn,
    Accelerometer_Yn,
    Accelerometer_Zn,
};
// Setup Neuton library, should be called once
neuton_nn_setup();

// Feed and prepare raw inputs for the model inference
neuton_input_features_t* p_input_features = neuton_nn_feed_inputs(raw_features, neuton_nn_uniq_inputs_num() * neuton_nn_input_window_size());

// Check if input data is prepared and ready for model inference
if (p_input_features)
{
    // Run model inference
    neuton_u16_t predicted_target;
    const neuton_output_t* p_probabilities;
    neuton_i16_t outputs_num = neuton_nn_run_inference(p_input_features, 
                                                        &predicted_target, 
                                                        &p_probabilities);

    // Check if model inference is ready and successful
    if (outputs_num > 0)
    {
        printf("Predicted target %d with probability %f\r\n", predicted_target, p_probabilities[predicted_target]);

        printf("All probabilities:\r\n");
        for (size_t i = 0; i < outputs_num; i++)
        {
            printf("%f,", p_probabilities[i]);
        }
        printf("\r\n");
    }
}
```

### Model Inference for Regression

``` C
// Check if input data is prepared and ready for model inference
if (p_input_features)
{
    // Run model inference
    const neuton_output_t* p_predicted_values;
    neuton_i16_t outputs_num = neuton_nn_run_inference(p_input_features,
                                                        NULL,
                                                        &p_predicted_values);

    // Check if model inference is ready and successful
    if (outputs_num > 0)
    {
        printf("Predicted target values:\r\n");
        for (size_t i = 0; i < outputs_num; i++)
        {
            printf("%f,", p_predicted_values[i]);
        }
        printf("\r\n");
    }
}
```

### Model Inference for Anomaly Detection


In anomaly detection mode, the model's inference yields an Anomaly Score, indicating the similarity of input data to the "normal" data used for training. A higher Anomaly Score signifies greater deviation from the normal data, while a score close to zero indicates normal data. Because the model learns only from normal data, it cannot predict the presence of anomalies, only deviation from the normal data, so user must set a threshold based on the Anomaly Score to identify anomalies.

``` C
// User should define Anomaly Score Threshold to identify anomalies by himself,
// specific to user application
#define USER_DEFINED_ANOMALY_SCORE_THRESHOLD 0.6f

// Check if input data is prepared and ready for model inference
if (p_input_features)
{
    // Run model inference
    neuton_u16_t anomaly_score_index;
    const neuton_output_t* p_anomaly_score;
    neuton_i16_t outputs_num = neuton_nn_run_inference(p_input_features,
                                                        &anomaly_score_index,
                                                        &p_anomaly_score);

    // Check if model inference is ready and successful
    if (outputs_num > 0)
    {
        neuton_output_t anomaly_score = p_anomaly_score[anomaly_score_index];
        printf("Predicted Anomaly score: %f\r\n", anomaly_score);

        if (anomaly_score > USER_DEFINED_ANOMALY_SCORE_THRESHOLD)
        {
            printf("Anomaly detected!\n");
        }
    }
}
```

### Library time limit for Zero Gravity plan
On Zero Gravity plan the `neuton_nn_run_inference` will return `NEUTON_NN_ERR_FREE_LIMIT_EXPIRED` as a result when library free time limit is expired:

``` C
// ...
// Run model inference
neuton_u16_t predicted_target;
const neuton_output_t* p_probabilities;
neuton_i16_t outputs_num = neuton_nn_run_inference(p_input_features, &predicted_target, &p_probabilities);

// Check if model inference is ready and successful
if (outputs_num > 0)
{
    printf("Predicted target %d with probability %f\r\n", predicted_target, p_probabilities[predicted_target]);

    printf("All probabilities:\r\n");
    for (size_t i = 0; i < outputs_num; i++)
        printf("%f,", p_probabilities[i]);
    printf("\r\n");
} 
else if (outputs_num == NEUTON_NN_ERR_FREE_LIMIT_EXPIRED)
{
    printf("Library usage free time limit is expired, please contact support@neuton.ai\r\n");
}
```

### Additional solution information API

You can use the following API to get solution information:
* `neuton_nn_solution_id_str` - Get user solution ID in string format;
* `neuton_nn_uniq_inputs_num` - Get number of unique input features on which the model was trained;
* `neuton_nn_input_window_size` - Get input features window size in feature samples(vectors);
* `neuton_nn_model_neurons_num` - Get number of model neurons;
* `neuton_nn_model_weights_num` - Get number of model weights;
* `neuton_nn_model_outputs_num` - Get number of model outputs (predicted targets);
* `neuton_nn_model_task` - Get model task : NEUTON_NN_TASK_MULT_CLASS, NEUTON_NN_TASK_BIN_CLASS, NEUTON_NN_TASK_REGRESSION
* `neuton_nn_model_size` - Get model size in bytes (flash usage)
* `neuton_nn_model_quantization` - Get model quantization (8/16/32 bit)
* `neuton_nn_model_activations_quantized` -  Check if model uses quantized activation functions
* `neuton_nn_input_scaling` - Get solution input scaling type: NEUTON_NN_INPUT_SCALING_UNIFIED, NEUTON_NN_INPUT_SCALING_UNIQUE