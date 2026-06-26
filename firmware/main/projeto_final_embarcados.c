#include <stdio.h>
#include "setup.h"

void app_main(void)
{
    adc_init();
    mpu6050_init();
    pwm_init();
    serial_init();
    gpio_init();
    init_rtos();
    printf("RTOS iniciado!\n");
}
