#ifndef PWM_H
#define PWM_H

#include "driver/ledc.h"
#include "joystick.h"

/* ================= CONFIG PWM ================= */

#define SERVO_RESOLUTION  LEDC_TIMER_12_BIT
#define SERVO_FREQ        50

#define PWM_X_GPIO        18
#define PWM_Y_GPIO        19

#define PWM_X_CHANNEL     LEDC_CHANNEL_0
#define PWM_Y_CHANNEL     LEDC_CHANNEL_1

/* ================= SERVO LIMITES ================= */

#define SERVO_MIN_DUTY    250   
#define SERVO_MAX_DUTY    360

/* ================= ADC ================= */

#define ADC_MAX_VALUE     4095

/* ================= FILTRO ================= */

#define DEADZONE          80
#define ALPHA             0.15f

/* ================= API ================= */

void pwm_init(void);
void atualizarPWM(Joystick_t *entrada);

#endif