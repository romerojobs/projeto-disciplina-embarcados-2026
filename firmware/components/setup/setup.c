#include "setup.h"

void init_rtos(){
    
    xQueuePWM = xQueueCreate(1, sizeof(Joystick_t));
    xQueueSerial = xQueueCreate(1, sizeof(Joystick_t));
    xMutexUART = xSemaphoreCreateMutex();
    
    xTaskCreate
    (
      TaskJoystick,
      "Joystick",
      2048,
      NULL,
      2,
      NULL
    );

    xTaskCreate
    (
      TaskPWM,
      "PWM",
      2048,
      NULL,
      1,
      NULL
    );
    
    xTaskCreate
    (
      TaskSerial,
      "ComunicaSerial",
      4096,
      NULL,
      1,
      NULL
    );
}