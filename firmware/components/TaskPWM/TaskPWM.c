#include "TaskPWM.h"

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