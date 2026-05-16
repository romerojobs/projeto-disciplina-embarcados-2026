#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adc.h"
#include "pwm.h"
#include "serial.h"
#include "joystick.h"

#define AMOSTRAGEM_PERIODO 10
#define PERIODO_PWM 10
#define PERIODO_MENSAGEM 500

QueueHandle_t xQueuePWM, xQueueSerial;

void taskJoystick(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
      Joystick_t valores = lerADC();

      xQueueOverwrite(xQueuePWM,&valores);
      xQueueOverwrite(xQueueSerial,&valores);
      vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(AMOSTRAGEM_PERIODO));
    }
}

void taskPWM(void *pvParameters)
{
    while(1)
    {
      Joystick_t para_pwm;
      xQueueReceive(xQueuePWM, &para_pwm,portMAX_DELAY);
                    printf("PWM: X=%d Y=%d\n",
               para_pwm.x,
               para_pwm.y);
      atualizarPWM(&para_pwm);
    }
}

void taskSerial(void *pvParameters)
{
    while(1)
    {
      Joystick_t para_enviar;
      xQueueReceive(xQueueSerial,&para_enviar,portMAX_DELAY);
      enviar_serial(&para_enviar);
    }
}

void app_main() {
  
    adc_init();
    pwm_init();

    xQueuePWM = xQueueCreate(1, sizeof(Joystick_t));
    xQueueSerial = xQueueCreate(1, sizeof(Joystick_t));

    xTaskCreate
    (
      taskJoystick,
      "Joystick",
      2048,
      NULL,
      2,
      NULL
    );

    xTaskCreate
    (
      taskPWM,
      "PWM",
      2048,
      NULL,
      1,
      NULL
    );
    
    xTaskCreate
    (
      taskSerial,
      "ComunicaSerial",
      4096,
      NULL,
      1,
      NULL
    );
}
