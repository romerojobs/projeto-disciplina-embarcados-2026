#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "global_data.h"
#include "adc.h"
#include "config.h"
#include "queues.h"
#include "mutexes.h"

void taskJoystick(void *pvParameters);
