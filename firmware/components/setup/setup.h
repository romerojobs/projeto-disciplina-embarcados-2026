#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adc.h"
#include "mpu.h"
#include "pwm.h"
#include "serial.h"
#include "global_data.h"
#include "mutexes.h"
#include "queues.h"
#include "TaskJoystick.h"
#include "TaskMPU.h"
#include "TaskPWM.h"
#include "TaskSerial.h"
#include "TaskVitoria.h"

void init_rtos(void);
