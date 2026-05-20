#include "TaskSerial.h"

void TaskSerial(void *pvParameters)
{
    Joystick_t valor_atual;

    while (1)
    {
      if (xQueuePeek(xQueueSerial, &valor_atual, 0) == pdTRUE)
      {
        enviar_serial(&valor_atual);  // só executa se a fila tinha dado válido
      }
      vTaskDelay(pdMS_TO_TICKS(PERIODO_SERIAL));
    }
}