#pragma once

#include "global_data.h"

void serial_init(void);
void enviar_serial(const mpu6050_raw_t *mpu);
