#include "TaskMPU.h"

void taskMPU(void *pvParameters)
{
    mpu6050_raw_t leitura;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        mpu6050_read(&leitura);
        if (xSemaphoreTake(xMutexDadosMPU, 0)) {
            dados_mpu_global = leitura;
            xSemaphoreGive(xMutexDadosMPU);
        }
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(AMOSTRAGEM_PERIODO));
    }
}
