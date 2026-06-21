#include "gpio.h"

void gpio_init(void)
{

    gpio_config_t sensor_vitoria_conf = 
    {
        .pin_bit_mask = (1ULL << SENSOR_VITORIA_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&sensor_vitoria_conf);


    gpio_config_t led_vitoria_conf = 
    {
        .pin_bit_mask = (1ULL << LED_VITORIA_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_vitoria_conf);

}