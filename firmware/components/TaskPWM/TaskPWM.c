#include "TaskPWM.h"

void taskPWM(void *pvParameters)
{
    Joystick_t para_pwm;
    
    while(1)
    {
      xQueueReceive(xQueuePWM, &para_pwm,portMAX_DELAY);
      atualizarPWM(&para_pwm);
    }
}