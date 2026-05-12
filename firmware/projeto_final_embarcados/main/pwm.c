#include <stdio.h>
#include "driver/ledc.h"
#include "joystick.h"
#include "pwm.h"

/**
 * Notas sobre o SG90:
 * Frequência: 50Hz (Período de 20ms)
 * 0 graus   : ~0.5ms de pulso
 * 180 graus : ~2.4ms de pulso
 * 
 * Se SERVO_RESOLUTION for LEDC_TIMER_12_BIT (4096 níveis):
 * MIN_DUTY = (0.5 / 20) * 4096 = 102
 * MAX_DUTY = (2.4 / 20) * 4096 = 491
 */

// Macros de cálculo baseadas na resolução definida no seu pwm.h
#define VALOR_MAX_RESOLUCAO ((1 << SERVO_RESOLUTION) - 1)
#define CALC_DUTY(ms)       ((uint32_t)((ms * VALOR_MAX_RESOLUCAO) / 20.0))

#define SERVO_MIN_DUTY    409               // 0 graus
#define SERVO_MAX_DUTY    1966              // 180 graus // Pulso de 2.4ms
#define ADC_MAX_VALUE       16383           // 14 bits do ADC do ESP32

/* Inicialização do PWM */
void pwm_init(void)
{
    // Configuração do Timer
    ledc_timer_config_t timer_config = {
        .speed_mode      = LEDC_LOW_SPEED_MODE,
        .timer_num       = LEDC_TIMER_0,
        .duty_resolution = SERVO_RESOLUTION, 
        .freq_hz         = SERVO_FREQ,       // Deve ser 50 para servos
        .clk_cfg         = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_config);

    // Configuração do Canal X
    ledc_channel_config_t canal_x = {
        .gpio_num   = PWM_X_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = PWM_X_CHANNEL,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = (SERVO_MIN_DUTY + SERVO_MAX_DUTY) / 2, // Inicia no centro
        .hpoint     = 0
    };

    // Configuração do Canal Y
    ledc_channel_config_t canal_y = {
        .gpio_num   = PWM_Y_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = PWM_Y_CHANNEL,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = (SERVO_MIN_DUTY + SERVO_MAX_DUTY) / 2, // Inicia no centro
        .hpoint     = 0
    };

    ledc_channel_config(&canal_x);
    ledc_channel_config(&canal_y);
}

/* Função auxiliar para mapeamento (Equivalente ao map() do Arduino) */
static uint32_t map_adc_to_servo(int32_t leitura_adc)
{
    // Garante que a leitura do ADC não ultrapasse os limites
    if (leitura_adc < 0) leitura_adc = 0;
    if (leitura_adc > ADC_MAX_VALUE) leitura_adc = ADC_MAX_VALUE;

    // Regra de três: (leitura * range_saida) / range_entrada + offset
    return (uint32_t)((leitura_adc * (SERVO_MAX_DUTY - SERVO_MIN_DUTY)) / ADC_MAX_VALUE) + SERVO_MIN_DUTY;
}

/* Atualização do PWM */
void atualizarPWM(Joystick_t *entrada)
{
    // Converte leitura do joystick em duty cycle
    uint32_t duty_x = map_adc_to_servo(entrada->x);
    uint32_t duty_y = map_adc_to_servo(entrada->y);

    // Debug: útil para calibrar se o servo está batendo no fim de curso
    printf("ADC [%4d, %4d] -> DUTY [%4lu, %4lu]\n", 
            entrada->x, entrada->y, duty_x, duty_y);

    // Aplica Canal X
    ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL, duty_x);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_X_CHANNEL);

    // Aplica Canal Y
    ledc_set_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL, duty_y);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, PWM_Y_CHANNEL);
}