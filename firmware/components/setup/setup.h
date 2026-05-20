#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adc.h"
#include "pwm.h"
#include "serial.h"
#include "joystick.h"
#include "mutexes.h"
#include "queues.h"

void init_rtos();