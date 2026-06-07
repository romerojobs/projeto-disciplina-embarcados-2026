#include <stdio.h>
#include <math.h>
#include "driver/uart.h"
#include "config.h"
#include "global_data.h"
#include "serial.h"

void serial_init(void)
{
    uart_config_t uart_config = {
        .baud_rate  = SERIAL_BAUD_RATE,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(SERIAL_UART_PORT, &uart_config);
    uart_set_pin(SERIAL_UART_PORT,
                 SERIAL_TX_GPIO, SERIAL_RX_GPIO,
                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(SERIAL_UART_PORT, 256, 0, 0, NULL, 0);
}

void enviar_serial(const mpu6050_raw_t *mpu)
{
    if (mpu == NULL) return;

    /* Converte aceleração bruta para g (escala ±2g: LSB = 16384) */
    float ax = mpu->ax / 16384.0f;
    float ay = mpu->ay / 16384.0f;
    float az = mpu->az / 16384.0f;

    /* Pitch: rotação em torno do eixo Y (inclinação frente/trás) */
    float pitch = atan2f(-ax, sqrtf(ay * ay + az * az)) * (180.0f / M_PI);

    /* Roll: rotação em torno do eixo X (inclinação lateral) */
    float roll  = atan2f(ay, az) * (180.0f / M_PI);

    char buf[64];
    int len = snprintf(buf, sizeof(buf),
                       "{\"pitch\": %.1f, \"roll\": %.1f}\n",
                       pitch, roll);
    uart_write_bytes(SERIAL_UART_PORT, buf, len);
}
