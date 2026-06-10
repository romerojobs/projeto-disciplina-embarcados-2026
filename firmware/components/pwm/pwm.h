#pragma once

#include "driver/ledc.h"
#include "global_data.h"
#include "config.h"

void pwm_init(void);
void atualizarPWM(Joystick_t *entrada);
