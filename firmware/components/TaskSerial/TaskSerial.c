#include "TaskSerial.h"

void TaskSerial(void *pvParameters)
{
    Joystick_t valor_atual;

    while (1)
    {
        xQueuePeek(xQueueSerial, &valor_atual, 0);  
        enviar_serial(&valor_atual);

        vTaskDelay(pdMS_TO_TICKS(PERIODO_SERIAL));
    }
}