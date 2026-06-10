#include "TaskPWM.h"

typedef struct {
    int buffer[MEDIA_MOVEL_JANELA];
    int soma;
    int indice;
    int amostras;
} MediaMovel_t;

static void media_movel_init(MediaMovel_t *f)
{
    for (int i = 0; i < MEDIA_MOVEL_JANELA; i++) f->buffer[i] = 0;
    f->soma = f->indice = f->amostras = 0;
}

static int media_movel_atualizar(MediaMovel_t *f, int nova_amostra)
{
    f->soma -= f->buffer[f->indice];
    f->buffer[f->indice] = nova_amostra;
    f->soma += nova_amostra;
    f->indice = (f->indice + 1) % MEDIA_MOVEL_JANELA;
    if (f->amostras < MEDIA_MOVEL_JANELA) f->amostras++;
    return f->soma / f->amostras;
}

void taskPWM(void *pvParameters)
{
    Joystick_t para_pwm = {0};
    Joystick_t filtrado;
    MediaMovel_t filtro_x, filtro_y;
    media_movel_init(&filtro_x);
    media_movel_init(&filtro_y);

    while (1) {
        xQueueReceive(xQueuePWM, &para_pwm, pdMS_TO_TICKS(20));

        filtrado.x = media_movel_atualizar(&filtro_x, para_pwm.x);
        filtrado.y = media_movel_atualizar(&filtro_y, para_pwm.y);

        atualizarPWM(&filtrado);
    }
}
