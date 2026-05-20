#include "esp_adc/adc_oneshot.h"
#include "joystick.h"

/* Inicialização do ADC */
void adc_init(void);

/* Leitura do joystick */
Joystick_t lerADC(void);