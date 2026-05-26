#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "joystick.h"
#include "config.h"
#include "queues.h"
#include "serial.h"

void TaskSerial(void *pvParameters);