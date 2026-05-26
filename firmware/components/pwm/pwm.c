#include <stdio.h>
#include "pwm.h"

/* ================= PWM INIT ================= */

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

/* ================= ATUALIZAR PWM ================= */

void atualizarPWM(Joystick_t *entrada)
{
    static int32_t duty_x = (SERVO_MIN_DUTY + SERVO_MAX_DUTY) / 2;
    static int32_t duty_y = (SERVO_MIN_DUTY + SERVO_MAX_DUTY) / 2;

    /* --- Eixo X --- */
    if (entrada->x > ADC_CENTER + JOYSTICK_THRESHOLD)
        duty_x += PWM_STEP;
    else if (entrada->x < ADC_CENTER - JOYSTICK_THRESHOLD)
        duty_x -= PWM_STEP;

    /* --- Eixo Y --- */
    if (entrada->y > ADC_CENTER + JOYSTICK_THRESHOLD)
        duty_y += PWM_STEP;
    else if (entrada->y < ADC_CENTER - JOYSTICK_THRESHOLD)
        duty_y -= PWM_STEP;

    /* --- Clamping --- */
    if (duty_x < SERVO_MIN_DUTY) duty_x = SERVO_MIN_DUTY;
    if (duty_x > SERVO_MAX_DUTY) duty_x = SERVO_MAX_DUTY;
    if (duty_y < SERVO_MIN_DUTY) duty_y = SERVO_MIN_DUTY;
    if (duty_y > SERVO_MAX_DUTY) duty_y = SERVO_MAX_DUTY;

    /* --- Escrita --- */
    ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL, (uint32_t)duty_x);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL);
    asm volatile("nop");
    ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL, (uint32_t)duty_y);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL);
}