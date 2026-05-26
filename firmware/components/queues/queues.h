#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

extern QueueHandle_t xQueuePWM;
extern QueueHandle_t xQueueSerial;