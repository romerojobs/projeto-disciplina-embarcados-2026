#pragma once

#include <stdint.h>

typedef struct {
    int x;
    int y;
} Joystick_t;

typedef struct {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    int16_t temp;
} mpu6050_raw_t;

extern mpu6050_raw_t  dados_mpu_global;
extern Joystick_t     dados_joystick_global;
