#include <stdio.h>
#include "setup.h"

void app_main() {
  
    adc_init();
    pwm_init();
    init_rtos();
    printf("RTOS iniciado!");
}
