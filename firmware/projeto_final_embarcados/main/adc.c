#include "esp_adc/adc_oneshot.h"
#include "joystick.h"
#include "adc.h"
/* Handle global do ADC */
static adc_oneshot_unit_handle_t adc1_handle;

/* Inicialização do ADC */
void adc_init(void)
{
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };

    adc_oneshot_new_unit(&init_config, &adc1_handle);

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_12,
    };

    /* GPIO34 -> ADC1_CHANNEL_6 */
    adc_oneshot_config_channel(
        adc1_handle,
        ADC_CHANNEL_6,
        &config
    );

    /* GPIO35 -> ADC1_CHANNEL_7 */
    adc_oneshot_config_channel(
        adc1_handle,
        ADC_CHANNEL_8,
        &config
    );
}

/* Leitura do joystick */
Joystick_t lerADC(void)
{
    Joystick_t leitura;

    adc_oneshot_read(
        adc1_handle,
        ADC_CHANNEL_6,
        &leitura.x
    );

    adc_oneshot_read(
        adc1_handle,
        ADC_CHANNEL_8,
        &leitura.y
    );

    return leitura;
}