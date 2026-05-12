#include "esp_adc/adc_oneshot.h"
#include "joystick.h"

/* Handle global do ADC */
static adc_oneshot_unit_handle_t adc1_handle;

/* Inicialização do ADC */
void adc_init(void);

/* Leitura do joystick */
Joystick_t lerADC(void);