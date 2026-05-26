#include "joystick.h"
#include "serial.h"
#include <stdio.h>

void enviar_serial(Joystick_t *entrada)
{
    if (entrada == NULL)
    {
        printf("[Serial] Erro: ponteiro nulo recebido.\n");
        return;
    }

    printf("[Joystick] X: %4d | Y: %4d\n", entrada->x, entrada->y);
}