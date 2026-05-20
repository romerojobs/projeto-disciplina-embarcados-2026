#include "TaskSerial.h"

void TaskSerial(void *pvParameters)
{
    while(1)
    {
      Joystick_t para_enviar;
      printf(); // Printa 
      xQueueReceive(xQueueSerial,&para_enviar,portMAX_DELAY);
      enviar_serial(&para_enviar);
    }
}