#pragma once

/* ============================================================
 *  Temporização
 * ============================================================ */
#define AMOSTRAGEM_PERIODO   10    /* ms — periodo das tasks de leitura  */
#define PERIODO_SERIAL       100   /* ms — periodo da TaskSerial          */
#define MEDIA_MOVEL_JANELA   8

/* ============================================================
 *  ADC — ESP32-S3
 *  ADC1_CHANNEL_6 = GPIO7  |  ADC1_CHANNEL_7 = GPIO8
 * ============================================================ */
#define ADC_JOYSTICK_X       ADC_CHANNEL_6
#define ADC_JOYSTICK_Y       ADC_CHANNEL_7
#define ADC_MAX_VALUE        4095

/* ============================================================
 *  PWM / Servo (LEDC)
 * ============================================================ */
#define SERVO_RESOLUTION     LEDC_TIMER_12_BIT
#define SERVO_FREQ           50
#define PWM_X_GPIO           5
#define PWM_Y_GPIO           4
#define PWM_X_CHANNEL        LEDC_CHANNEL_0
#define PWM_Y_CHANNEL        LEDC_CHANNEL_1
#define SERVO_MIN_DUTY       275
#define SERVO_MAX_DUTY       318
#define HISTERESE_DUTY       3

#define DUTY_X_OFFSET        -4
#define DUTY_Y_OFFSET        -4

/* ============================================================
 *  I2C / MPU6050
 * ============================================================ */
#define MPU6050_ADDR         0x68
#define MPU6050_REG_DATA     0x3B
#define MPU6050_I2C_PORT     I2C_NUM_0
#define I2C_SDA_GPIO         35
#define I2C_SCL_GPIO         36
#define I2C_FREQ_HZ          400000

#define PITCH_OFFSET         3.3
#define ROLL_OFFSET          0

#define PITCH_SENTIDO        -1
#define ROLL_SENTIDO         -1

/* ============================================================
 *  UART / Serial
 *  UART_NUM_0 = porta USB nativa do ESP32-S3
 * ============================================================ */
#define SERIAL_UART_PORT     UART_NUM_0
#define SERIAL_BAUD_RATE     115200
#define SERIAL_TX_GPIO       43    /* GPIO43 = UART0 TX no ESP32-S3 */
#define SERIAL_RX_GPIO       44    /* GPIO44 = UART0 RX no ESP32-S3 */

/* ============================================================
 *  Sensor de vitória
 * ============================================================ */

#define PERIODO_LEITURA_VITORIA 10
#define SENSOR_VITORIA_PIN GPIO_NUM_38
#define LED_VITORIA_PIN GPIO_NUM_37