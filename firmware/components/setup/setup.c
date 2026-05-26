#include "setup.h"

void init_rtos(){
    
    xQueuePWM = xQueueCreate(1, sizeof(Joystick_t));
    xQueueSerial = xQueueCreate(1, sizeof(Joystick_t));
    
    xTaskCreate
    (
      taskJoystick,
      "Joystick",
      2048,
      NULL,
      2,
      NULL
    );
    
    xTaskCreate
    (
      taskPWM,
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