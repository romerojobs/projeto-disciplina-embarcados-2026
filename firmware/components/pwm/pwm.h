#ifndef PWM_H
#define PWM_H

#include "driver/ledc.h"
#include "joystick.h"

/* ================= CONFIG PWM ================= */

#define SERVO_RESOLUTION  LEDC_TIMER_12_BIT
#define SERVO_FREQ        50

#define PWM_X_GPIO        4
#define PWM_Y_GPIO        5

#define PWM_X_CHANNEL     LEDC_CHANNEL_0
#define PWM_Y_CHANNEL     LEDC_CHANNEL_1

/* ================= SERVO LIMITES ================= */

//#define SERVO_MIN_DUTY    102 // 0
//#define SERVO_MAX_DUTY    491 // 180

#define SERVO_MIN_DUTY    275 // 80
#define SERVO_MAX_DUTY    318 // 100



/* ================= ADC ================= */

#define ADC_MAX_VALUE     4095

/* ================= HISTERESE ================= */

#define HISTERESE_DUTY    3

/* ================= API ================= */

void pwm_init(void);
void atualizarPWM(Joystick_t *entrada);

#endif