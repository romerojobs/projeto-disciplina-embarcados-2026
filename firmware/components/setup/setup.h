#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adc.h"
#include "pwm.h"
#include "serial.h"
#include "joystick.h"
#include "mutexes.h"
#include "queues.h"
#include "TaskJoystick.h"
#include "TaskPWM.h"
#include "TaskSerial.h"


void init_rtos();