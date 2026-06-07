#include "esp_adc/adc_oneshot.h"
#include "config.h"
#include "global_data.h"
#include "adc.h"

static adc_oneshot_unit_handle_t adc1_handle;

void adc_init(void)
{
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init_config, &adc1_handle);

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten    = ADC_ATTEN_DB_12,
    };

    adc_oneshot_config_channel(adc1_handle, ADC_JOYSTICK_X, &config);
    adc_oneshot_config_channel(adc1_handle, ADC_JOYSTICK_Y, &config);
}

Joystick_t lerADC(void)
{
    Joystick_t leitura;
    adc_oneshot_read(adc1_handle, ADC_JOYSTICK_X, &leitura.x);
    adc_oneshot_read(adc1_handle, ADC_JOYSTICK_Y, &leitura.y);
    return leitura;
}
