#include "driver/ledc.h"
#include "joystick.h"


#define SERVO_RESOLUTION  LEDC_TIMER_14_BIT // 12 bits é o ideal para servos no ESP32
#define SERVO_FREQ        50                // Frequência padrão de servos
#define PWM_X_GPIO        18                // Seu pino aqui
#define PWM_Y_GPIO        19                // Seu pino aqui
#define PWM_X_CHANNEL     LEDC_CHANNEL_0
#define PWM_Y_CHANNEL     LEDC_CHANNEL_1

/* Inicialização do PWM */
void pwm_init(void);

/* Atualização do PWM */
void atualizarPWM(Joystick_t *entrada);