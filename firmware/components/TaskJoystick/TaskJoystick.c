#include "TaskJoystick.h"

void taskJoystick(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        Joystick_t valores = lerADC();
        valores.x = 4095 - valores.x;  /* Eixo X invertido */
        valores.y = valores.y;  /* Eixo Y invertido */

        xQueueOverwrite(xQueuePWM, &valores);

        if (xSemaphoreTake(xMutexDadosADC, 0)) {
            dados_joystick_global = valores;
            xSemaphoreGive(xMutexDadosADC);
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(AMOSTRAGEM_PERIODO));
    }
}
