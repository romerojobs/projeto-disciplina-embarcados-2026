#include <stdio.h>
#include <math.h>
#include "pwm.h"

/* estado do filtro */
static float filtro_x = 0;
static float filtro_y = 0;

/* ================= UTIL ================= */

static uint32_t map_adc_to_servo(int32_t v)
{
    if (v < 0) v = 0;
    if (v > ADC_MAX_VALUE) v = ADC_MAX_VALUE;

    return (uint32_t)((v * (SERVO_MAX_DUTY - SERVO_MIN_DUTY)) / ADC_MAX_VALUE)
           + SERVO_MIN_DUTY;
}

static float apply_deadzone(float v)
{
    float center = ADC_MAX_VALUE / 2;

    if (fabsf(v - center) < DEADZONE)
        return center;

    return v;
}

static float low_pass(float input, float prev)
{
    return (ALPHA * input) + ((1.0f - ALPHA) * prev);
}

/* ================= PWM ================= */

void pwm_init(void)
{
    ledc_timer_config_t timer_config = {
        .speed_mode      = LEDC_LOW_SPEED_MODE,
        .timer_num       = LEDC_TIMER_0,
        .duty_resolution = SERVO_RESOLUTION,
        .freq_hz         = SERVO_FREQ,
        .clk_cfg         = LEDC_AUTO_CLK
    };

    ledc_timer_config(&timer_config);

    ledc_channel_config_t canal_x = {
        .gpio_num   = PWM_X_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = PWM_X_CHANNEL,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = (SERVO_MIN_DUTY + SERVO_MAX_DUTY) / 2,
        .hpoint     = 0
    };

    ledc_channel_config_t canal_y = {
        .gpio_num   = PWM_Y_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = PWM_Y_CHANNEL,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = (SERVO_MIN_DUTY + SERVO_MAX_DUTY) / 2,
        .hpoint     = 0
    };

    ledc_channel_config(&canal_x);
    ledc_channel_config(&canal_y);
}

void atualizarPWM(Joystick_t *entrada)
{
    float x = apply_deadzone((float)entrada->x);
    float y = apply_deadzone((float)entrada->y);

    filtro_x = low_pass(x, filtro_x);
    filtro_y = low_pass(y, filtro_y);

    uint32_t duty_x = map_adc_to_servo((int32_t)filtro_x);
    uint32_t duty_y = map_adc_to_servo((int32_t)filtro_y);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL, duty_x);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL, duty_y);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL);
}