/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <soc.h>
#include <stddef.h>
#include <string.h>
#include <zephyr/types.h>

#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/usb/usb_device.h>

#include <neuton/neuton.h>
#include <neuton/neuton_version.h>
#include <button/bsp_button.h>
#include <led/bsp_led.h>
#include <sensor/imu/bsp_imu.h>

#include "ble/gatt/ble_gatt.h"
#include "inference_postprocessing.h"

//////////////////////////////////////////////////////////////////////////////

#define ACCEL_AXIS_NUM (3U)
#define GYRO_AXIS_NUM (3U)
#define NEUTON_INPUT_DATA_LEN (ACCEL_AXIS_NUM + GYRO_AXIS_NUM)

#define LED_MAX_BRIGHTNESS (0.2f)
#define LED_BLINK_CHANGE_BRIGHTNESS_STEP (0.005f)

#define SERVICE_THREAD_STACK_SIZE 1024
#define SERVICE_THREAD_PRIORITY   5
#define SERVICE_THREAD_PERIOD_MS  30

#define PRINT_RSSI_INTERVAL_MS 5000

LOG_MODULE_REGISTER(main);

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief Application remote control mode
 *
 */
typedef enum app_remotectrl_mode_e
{
    /**
     * APP_REMOTECTRL_MODE_PRESENTATION used for slides control:
     * - Swipe Right                       = KEY_ARROW_RIGHT (Next slide)
     * - Swipe Left                        = KEY_ARROW_LEFT  (Previous slide)
     * - Double Tap                        = KEY_F5          (Enter fullscreen mode)
     * - Double Thumb                      = KEY_ESC         (Exit fullscreen mode)
     * - Rotation Clockwise (Right)        = Not used
     * - Rotation Counter Clockwise (Left) = Not used
     *
     */
    APP_REMOTECTRL_MODE_PRESENTATION = 0,

    /**
     * NEUTON_REMOTE_CTRL_MUSIC used for music/media control:
     * - Swipe Right                       = KEY_MEDIA_NEXT_TRACK  (Next track)
     * - Swipe Left                        = KEY_MEDIA_PREV_TRACK  (Previous track)
     * - Double Tap                        = KEY_MEDIA_PLAYPAUSE   (Play/Pause)
     * - Double Thumb                      = KEY_MEDIA_MUTE        (Mute)
     * - Rotation Clockwise (Right)        = KEY_MEDIA_VOLUMEUP    (Volume Up)
     * - Rotation Counter Clockwise (Left) = KEY_MEDIA_VOLUMEDOWN  (Volume Down)
     */
    APP_REMOTECTRL_MODE_MUSIC
} app_remotectrl_mode_t;

typedef int (*led_set_func_t)(float brightness);

//////////////////////////////////////////////////////////////////////////////

static void board_support_init_(void);
static void imu_data_ready_cb_(void);
static void ble_connection_cb_(bool connected);
static void button_click_handler_(bool pressed);
static void ble_send_recognized_class_(const class_label_t class_label, size_t probability_pct);
static void neuton_prediction_handler_(const class_label_t class_label, 
                                        const float probability,
                                        const char* class_name,
                                        const bool is_raw);

static void service_thread_fn_(void *p1, void *p2, void *p3);

//////////////////////////////////////////////////////////////////////////////

static bool ble_connected_ = false;
static bool ble_adv_started_ = false;
static struct k_sem imu_data_ready_sem_;

//////////////////////////////////////////////////////////////////////////////

K_THREAD_DEFINE(led_thread_id, SERVICE_THREAD_STACK_SIZE,
                service_thread_fn_, NULL, NULL, NULL,
                SERVICE_THREAD_PRIORITY, 0, 0);

//////////////////////////////////////////////////////////////////////////////

int main(void)
{
    /** Initialize Board Support Package */
    board_support_init_();

    /** Initialize Neuton.AI library */
    neuton_nn_setup();

    printk("Neuton.AI Nordic Thingy 53 Gestures Recognition Demo: \r\n");
    printk("\t Version: %d.%d.%d\r\n", NEUTON_MAJOR_VERSION, NEUTON_MINOR_VERSION, NEUTON_PATCH_VERSION);
    printk("\t Solution id: %s\r\n", neuton_nn_solution_id_str());

    bsp_imu_data_t imu_data = {0};
    neuton_input_t input_data[NEUTON_INPUT_DATA_LEN];

    for (;;)
    {
        /** Wait for the semaphore to be released by IMU data ready interrupt */
        k_sem_take(&imu_data_ready_sem_, K_FOREVER);

        /** Read IMU sensor data sample */
        if (bsp_imu_read(&imu_data) != BSP_STATUS_SUCCESS)
            continue;

        input_data[0] = imu_data.accel[0].raw;
        input_data[1] = imu_data.accel[1].raw;
        input_data[2] = imu_data.accel[2].raw;
        input_data[3] = imu_data.gyro[0].raw;
        input_data[4] = imu_data.gyro[1].raw;
        input_data[5] = imu_data.gyro[2].raw;
        /** Feed and prepare raw sensor inputs for the model inference */
        /** If you need to collect data, uncomment the below line which will send the sensor readings to serial output (and comment out lines 133-151)*/
        /** printk("%d,%d,%d,%d,%d,%d\r\n",  input_data[0], input_data[1], input_data[2], input_data[3], input_data[4], input_data[5]);*/ 
        neuton_input_features_t* p_input = neuton_nn_feed_inputs(input_data, NEUTON_INPUT_DATA_LEN);

        /** Check if input data window is ready for inference */
        if (p_input)
        {
            neuton_u16_t predicted_target;
            const neuton_output_t* p_probabilities;

            /** Run Neuton model inference */
            neuton_i16_t targets_num = neuton_nn_run_inference(p_input, &predicted_target, &p_probabilities);

            /** Handle Neuton inference results if the prediction was
             * successful */
            if (targets_num > 0)
            {
                bool do_postprocessing = true;
                inference_postprocess(predicted_target,
                                      p_probabilities[predicted_target],
                                      do_postprocessing,
                                      neuton_prediction_handler_);
            }
        }
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////

static void board_support_init_(void)
{
    int ret;

    /** Initialize LEDs */
    ret = bsp_led_init();
    if (ret != 0)
    {
        printk("Failed to initialize LEDs module, error = %d\n", ret);
    }

    /** Initialize user button */
    ret = bsp_button_init();
    if (ret != 0)
    {
        printk("Failed to initialize user button, error = %d\n", ret);
    }
    bsp_button_reg_click_handler(button_click_handler_);

    /** Initialize IMU sensor  */
    bsp_imu_config_t imu_config = 
    {
        .accel_fs_g = BSP_IMU_ACCEL_SCALE_4G,
        .gyro_fs_dps = BSP_IMU_ACCEL_SCALE_1000DPS,
        .data_rate_hz = 100
    };

    bsp_status_t status = bsp_imu_init(&imu_config, imu_data_ready_cb_);
    if (status != BSP_STATUS_SUCCESS)
    {
        printk("Failed to initialize IMU sensor, error = %d\n", (int)status);
    }
    k_sem_init(&imu_data_ready_sem_, 0, 1); // Initial count 0, max count 1

    /** Initialize BLE HID profile */
    ret = ble_gatt_init(ble_connection_cb_, NULL);
    if (ret != 0)
    {
        printk("Failed to initialize BLE HID service\n");
    }

    ble_adv_started_ = true;
}

//////////////////////////////////////////////////////////////////////////////

static void button_click_handler_(bool pressed)
{
    if (pressed)
    {
        bsp_led_off();
    }
}

//////////////////////////////////////////////////////////////////////////////

static void ble_connection_cb_(bool connected)
{
    ble_connected_ = connected;
    ble_adv_started_ = false;
    bsp_led_off();
}

//////////////////////////////////////////////////////////////////////////////

static void imu_data_ready_cb_(void)
{
    k_sem_give(&imu_data_ready_sem_); // Release the semaphore
}

//////////////////////////////////////////////////////////////////////////////

static void neuton_prediction_handler_(const class_label_t class_label, 
                                        const float probability,
                                        const char* class_name,
                                        const bool is_raw)
{
    static const uint32_t PREDICTION_TIMEOUT_MS = 800U;
    size_t probability_pct = (size_t)(100 * probability);

    if (is_raw)
    {
        printk("RAW Prediction %s %d %%\r\n", class_name, probability_pct);
    }
    else if (class_label != CLASS_LABEL_UNKNOWN && class_label != CLASS_LABEL_IDLE)
    {
        static uint32_t last_prediction_time_ms_ = 0;
        uint32_t current_time_ms = k_uptime_get();

        /** For classes CLASS_LABEL_ROTATION_RIGHT & CLASS_LABEL_ROTATION_LEFT there is no timeout,
         * since the movements must be repetitive in time
         */
        if ((class_label == CLASS_LABEL_ROTATION_RIGHT) ||
            (class_label == CLASS_LABEL_ROTATION_LEFT) ||
            (current_time_ms - last_prediction_time_ms_) > PREDICTION_TIMEOUT_MS)
        {
            last_prediction_time_ms_ = current_time_ms;

            printk("Predicted class: %s, with probability %d %%\r\n", class_name, probability_pct);

            ble_send_recognized_class_(class_label, probability_pct);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

static void ble_send_recognized_class_(const class_label_t class_label, size_t probability_pct)
{
    static char send_buff[15] = {0};
    memset(send_buff, 0, sizeof(send_buff));

    snprintf(send_buff, sizeof(send_buff), "%d,%d", (int)class_label, (int)probability_pct);

    ble_gatt_send_raw_data((const uint8_t*)&send_buff, strlen(send_buff));
}

//////////////////////////////////////////////////////////////////////////////

static void service_thread_fn_(void *p1, void *p2, void *p3)
{
    static bool rising = true;
    static float brightness = 0;

    while (1)
    {
        if (ble_connected_)
        {
            bsp_led_set_green(brightness);
        }
        else
        {
            bsp_led_set_red(brightness);
        }

        if (rising)
        {
            brightness += LED_BLINK_CHANGE_BRIGHTNESS_STEP;
            if (brightness >= LED_MAX_BRIGHTNESS)
                rising = false;
        }
        else
        {
            brightness -= LED_BLINK_CHANGE_BRIGHTNESS_STEP;
            if (brightness <= 0)
                rising = true;
        }

        if (!ble_connected_ && !ble_adv_started_)
        {
            int err = ble_gatt_start_advertising();

            if (err)
            {
                printk("Advertising failed to start (err %d)\n", err);
            }
            else
            {
                ble_adv_started_ = true;
            }
        }

        k_msleep(SERVICE_THREAD_PERIOD_MS);
    }
}