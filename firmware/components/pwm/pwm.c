#include <stdio.h>
#include <stdlib.h>
#include "pwm.h"

/* ================= UTIL ================= */

static uint32_t map_adc_to_servo(int32_t v)
{
    if (v < 0) v = 0;
    if (v > ADC_MAX_VALUE) v = ADC_MAX_VALUE;

    return (uint32_t)((v * (SERVO_MAX_DUTY - SERVO_MIN_DUTY)) / ADC_MAX_VALUE)
           + SERVO_MIN_DUTY;
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
    static uint32_t ultimo_duty_x = 0;
    static uint32_t ultimo_duty_y = 0;

    uint32_t duty_x = map_adc_to_servo(entrada->x) - 3;
    uint32_t duty_y = map_adc_to_servo(entrada->y) - 3;

    if (abs((int)duty_x - (int)ultimo_duty_x) > HISTERESE_DUTY)
    {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL, duty_x);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL);
        ultimo_duty_x = duty_x;
    }

    if (abs((int)duty_y - (int)ultimo_duty_y) > HISTERESE_DUTY)
    {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL, duty_y);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL);
        ultimo_duty_y = duty_y;
    }
}