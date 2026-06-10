#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "global_data.h"
#include "config.h"
#include "queues.h"
#include "pwm.h"

void taskPWM(void *pvParameters);
