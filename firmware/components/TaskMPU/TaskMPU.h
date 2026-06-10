#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "global_data.h"
#include "mpu.h"
#include "mutexes.h"
#include "config.h"

void taskMPU(void *pvParameters);
