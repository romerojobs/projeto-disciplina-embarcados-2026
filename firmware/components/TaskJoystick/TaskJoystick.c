#include "TaskJoystick.h"

void taskJoystick(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
      Joystick_t valores = lerADC();
      xQueueOverwrite(xQueuePWM,&valores);
      xSemaphoreTake( xMutexUART);
      printf("X: %d | Y: %d\n",valores->x, valores->y);
      vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(AMOSTRAGEM_PERIODO));
    }
}