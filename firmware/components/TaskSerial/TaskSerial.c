#include "TaskSerial.h"

void TaskSerial(void *pvParameters)
{
    mpu6050_raw_t valor_atual_mpu = {0};

    while (1) {
        if (xSemaphoreTake(xMutexDadosMPU, portMAX_DELAY)) {
            valor_atual_mpu = dados_mpu_global;
            xSemaphoreGive(xMutexDadosMPU);
        }

        enviar_serial(&valor_atual_mpu);

        vTaskDelay(pdMS_TO_TICKS(PERIODO_SERIAL));
    }
}
