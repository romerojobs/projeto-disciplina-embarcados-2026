#include "joystick.h"
#include "serial.h"
#include <stdio.h>

void enviar_serial(Joystick_t *entrada)
{
    printf("X: %d | Y: %d\n",
           entrada->x,
           entrada->y);
}