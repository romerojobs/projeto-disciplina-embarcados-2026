#include "joystick.h"
#include "serial.h"
#include <stdio.h>

void enviar_serial(Joystick_t *entrada)
{
    printf("%d %d", entrada->x, entrada->y);
}