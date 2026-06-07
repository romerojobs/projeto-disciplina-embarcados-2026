#pragma once

#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "global_data.h"
#include "config.h"

void mpu6050_init(void);
void mpu6050_read(mpu6050_raw_t *data);
