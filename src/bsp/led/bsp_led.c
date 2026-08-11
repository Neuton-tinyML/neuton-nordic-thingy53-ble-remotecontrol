#include "bsp_led.h"
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

//////////////////////////////////////////////////////////////////////////////
/*
 * Backend chosen from the devicetree:
 *   PWM  - pwm-led0/1/2 aliases (Thingy:53). Real brightness control.
 *   GPIO - led-red/green/blue aliases (nRF54L15 TAG). Plain GPIOs, so
 *          brightness collapses to on/off and a ramp blinks instead of fading.
 */
#if DT_NODE_EXISTS(DT_ALIAS(pwm_led0))
#define BSP_LED_BACKEND_PWM 1
#elif DT_NODE_EXISTS(DT_ALIAS(led_red))
#define BSP_LED_BACKEND_GPIO 1
#else
#error "Board provides neither pwm-led0..2 nor led-red/green/blue aliases"
#endif

//////////////////////////////////////////////////////////////////////////////
#if defined(BSP_LED_BACKEND_PWM)

#include <zephyr/drivers/pwm.h>

static const struct pwm_dt_spec red_pwm_led_ = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
static const struct pwm_dt_spec green_pwm_led_ = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));
static const struct pwm_dt_spec blue_pwm_led_ = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led2));

//////////////////////////////////////////////////////////////////////////////

// not calibrated, fixed for specific board
#define PWM_PERIOD PWM_MSEC(20)

//////////////////////////////////////////////////////////////////////////////

static int init_led_(const struct pwm_dt_spec pwm_led)
{
    int ret = 0;
    if (!device_is_ready(pwm_led.dev))
    {
        printk("PWM LED Init error '%s' device_is_ready()\n", pwm_led.dev->name);
        return ret;
    }

    ret = pwm_set_dt(&pwm_led, PWM_PERIOD, 0);
    if (ret)
    {
        printk("Error %d: failed to set pulse width for %s\n", ret, pwm_led.dev->name);
        return ret;
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

static int set_led_(const struct pwm_dt_spec pwm_led, float brightness)
{
    int ret = 0;
    uint32_t pulse = brightness * PWM_PERIOD;
    ret = pwm_set_pulse_dt(&pwm_led, pulse);
    if (ret < 0)
    {
        printk("LED Init error pwm_set_pulse_dt()\n");
        return ret;
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_init(void)
{
    int ret;
    ret = init_led_(red_pwm_led_);
    BSP_RETURN_IF(ret != 0, ret);

    ret = init_led_(green_pwm_led_);
    BSP_RETURN_IF(ret != 0, ret);

    ret = init_led_(blue_pwm_led_);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_red(float brightness)
{
    pwm_set_pulse_dt(&green_pwm_led_, 0);
    pwm_set_pulse_dt(&blue_pwm_led_, 0);
    return set_led_(red_pwm_led_, brightness);
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_green(float brightness)
{
    pwm_set_pulse_dt(&red_pwm_led_, 0);
    pwm_set_pulse_dt(&blue_pwm_led_, 0);
    return set_led_(green_pwm_led_, brightness);
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_blue(float brightness)
{
    pwm_set_pulse_dt(&red_pwm_led_, 0);
    pwm_set_pulse_dt(&green_pwm_led_, 0);
    return set_led_(blue_pwm_led_, brightness);
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_rgb(float r, float g, float b)
{
    int ret;
    uint32_t red = r * PWM_PERIOD;
    uint32_t green = g * PWM_PERIOD;
    uint32_t blue = b * PWM_PERIOD;
    ret = pwm_set_pulse_dt(&red_pwm_led_, red);
    BSP_RETURN_IF(ret != 0, ret);

    ret = pwm_set_pulse_dt(&green_pwm_led_, green);
    BSP_RETURN_IF(ret != 0, ret);

    ret = pwm_set_pulse_dt(&blue_pwm_led_, blue);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_off(void)
{
    int ret;
    ret = pwm_set_pulse_dt(&red_pwm_led_, 0);
    BSP_RETURN_IF(ret != 0, ret);

    ret = pwm_set_pulse_dt(&green_pwm_led_, 0);
    BSP_RETURN_IF(ret != 0, ret);

    ret = pwm_set_pulse_dt(&blue_pwm_led_, 0);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////
#elif defined(BSP_LED_BACKEND_GPIO)

#include <zephyr/drivers/gpio.h>

/* Any brightness at or above this lights the LED. Deliberately well below the
 * application's peak brightness so that a ramped value still crosses it and the
 * LED blinks, rather than sitting permanently on. */
#define BSP_LED_ON_THRESHOLD (0.05f)

static const struct gpio_dt_spec red_led_ = GPIO_DT_SPEC_GET(DT_ALIAS(led_red), gpios);
static const struct gpio_dt_spec green_led_ = GPIO_DT_SPEC_GET(DT_ALIAS(led_green), gpios);
static const struct gpio_dt_spec blue_led_ = GPIO_DT_SPEC_GET(DT_ALIAS(led_blue), gpios);

//////////////////////////////////////////////////////////////////////////////

static int init_led_(const struct gpio_dt_spec* p_led)
{
    if (!device_is_ready(p_led->port))
    {
        printk("GPIO LED Init error '%s' device_is_ready()\n", p_led->port->name);
        return ENODEV;
    }

    /* Active level comes from the devicetree flags, so INACTIVE means "off"
     * whether the LED is wired active-high or active-low. */
    return gpio_pin_configure_dt(p_led, GPIO_OUTPUT_INACTIVE);
}

//////////////////////////////////////////////////////////////////////////////

static int set_led_(const struct gpio_dt_spec* p_led, float brightness)
{
    return gpio_pin_set_dt(p_led, (brightness >= BSP_LED_ON_THRESHOLD) ? 1 : 0);
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_init(void)
{
    int ret;
    ret = init_led_(&red_led_);
    BSP_RETURN_IF(ret != 0, ret);

    ret = init_led_(&green_led_);
    BSP_RETURN_IF(ret != 0, ret);

    ret = init_led_(&blue_led_);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_red(float brightness)
{
    set_led_(&green_led_, 0.0f);
    set_led_(&blue_led_, 0.0f);
    return set_led_(&red_led_, brightness);
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_green(float brightness)
{
    set_led_(&red_led_, 0.0f);
    set_led_(&blue_led_, 0.0f);
    return set_led_(&green_led_, brightness);
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_blue(float brightness)
{
    set_led_(&red_led_, 0.0f);
    set_led_(&green_led_, 0.0f);
    return set_led_(&blue_led_, brightness);
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_set_rgb(float r, float g, float b)
{
    int ret;
    ret = set_led_(&red_led_, r);
    BSP_RETURN_IF(ret != 0, ret);

    ret = set_led_(&green_led_, g);
    BSP_RETURN_IF(ret != 0, ret);

    ret = set_led_(&blue_led_, b);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_off(void)
{
    int ret;
    ret = set_led_(&red_led_, 0.0f);
    BSP_RETURN_IF(ret != 0, ret);

    ret = set_led_(&green_led_, 0.0f);
    BSP_RETURN_IF(ret != 0, ret);

    ret = set_led_(&blue_led_, 0.0f);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////
#endif /* backend selection */

//////////////////////////////////////////////////////////////////////////////
/* Backend-agnostic below: these build on the primitives defined above. */

int bsp_led_blink_red(float brightness, int32_t on_ms, int32_t off_ms)
{
    int ret;
    ret = bsp_led_set_red(brightness);
    BSP_RETURN_IF(ret != 0, ret);

    k_msleep(on_ms);

    ret = bsp_led_off();

    k_msleep(off_ms);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_blink_green(float brightness, int32_t on_ms, int32_t off_ms)
{
    int ret;
    ret = bsp_led_set_green(brightness);
    BSP_RETURN_IF(ret != 0, ret);

    k_msleep(on_ms);

    ret = bsp_led_off();

    k_msleep(off_ms);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_blink_blue(float brightness, int32_t on_ms, int32_t off_ms)
{
    int ret;
    ret = bsp_led_set_blue(brightness);
    BSP_RETURN_IF(ret != 0, ret);

    k_msleep(on_ms);

    ret = bsp_led_off();

    k_msleep(off_ms);
    return ret;
}

//////////////////////////////////////////////////////////////////////////////

int bsp_led_blink_rgb(float r, float g, float b, int32_t on_ms, int32_t off_ms)
{
    int ret;
    ret = bsp_led_set_rgb(r, g, b);

    BSP_RETURN_IF(ret != 0, ret);

    k_msleep(on_ms);

    ret = bsp_led_off();

    k_msleep(off_ms);
    return ret;
}