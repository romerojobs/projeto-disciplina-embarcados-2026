#include "TaskJoystick.h"

void taskJoystick(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
      Joystick_t valores = lerADC();
      valores.y = 4095-valores.y; // Valor invertido!!!
      xQueueOverwrite(xQueuePWM,&valores);
      xQueueOverwrite(xQueueSerial,&valores);
      vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(AMOSTRAGEM_PERIODO));
    }
}